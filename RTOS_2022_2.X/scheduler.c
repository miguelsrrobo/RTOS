#include "scheduler.h"
#include "types.h"

extern ready_queue_t READY_queue;

void scheduler()
{
#if RR_SCHEDULER == TRUE
   READY_queue.pos_task_running = RR_scheduler();
#elif PRIOR_SCHEDULER == TRUE
   READY_queue.pos_task_running = PRIOR_scheduler();
#endif   
}

u_int RR_scheduler()
{
   u_int next_task = READY_queue.pos_task_running;
   
   do {
      next_task = (next_task+1) % READY_queue.ready_queue_size;
   } while (READY_queue.tasks[next_task].task_state != READY);
   
   return next_task;
}

u_int PRIOR_scheduler()
{
#if NO_PRE_SCHEDULER == TRUE
   READY_queue.pos_task_running = NO_PRE_scheduler();
#elif PRE_SCHEDULER == TRUE
   READY_queue.pos_task_running = PRE_scheduler();
#endif   
}

u_int NO_PRE_scheduler(){
    int pos_task_priority = 0;
//    int pos_task_priority = 0;
    u_int next_task = READY_queue.pos_task_running;
//    for(int i = 0; i < READY_queue.ready_queue_size;i++)
//    {
//      next_task = i;
//    }
    for(int i = 0; i < READY_queue.ready_queue_size; i++){
        if (READY_queue.tasks[i].task_prior > pos_task_priority)
        {
            pos_task_priority = READY_queue.tasks[i].task_prior;
            next_task = i;
        }
    }
    return next_task;
}

u_int PRE_scheduler(){
    int pos_task_priority = 0;
    u_int next_task = READY_queue.pos_task_running;
    for(int i = 0; i < READY_queue.ready_queue_size; i++){
        if (READY_queue.tasks[i].task_prior > pos_task_priority)
        {
            pos_task_priority = READY_queue.tasks[i].task_prior;
            next_task = i;
        }
    }
    return next_task;
}
