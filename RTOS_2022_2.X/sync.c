#include "sync.h"
#include "kernel.h"
#include "scheduler.h"

extern ready_queue_t READY_queue;

void sem_init(sem_t *sem, u_int value)
{
   di();
   sem->s_value            = value;
   sem->s_queue.pos_in     = 0;
   sem->s_queue.pos_out    = 0;
   ei();
}

void sem_wait(sem_t *sem)
{
   di();
   sem->s_value--;
   if (sem->s_value < 0) {
      sem->s_queue.blocked_queue[sem->s_queue.pos_in] = READY_queue.pos_task_running;
      sem->s_queue.pos_in = (sem->s_queue.pos_in + 1) % MAX_USER_TASKS;
      SAVE_CONTEXT(BLOCKED_SEM);
      scheduler();
      RESTORE_CONTEXT();
   }
   ei();
}

void sem_post(sem_t *sem)
{
   di();
   sem->s_value++;
   if (sem->s_value <= 0) {
      //change_task_state(sem->s_queue.pos_out, READY);
      READY_queue.tasks[sem->s_queue.pos_out].task_state = READY;
      sem->s_queue.pos_out = (sem->s_queue.pos_out + 1) % MAX_USER_TASKS;
      SAVE_CONTEXT(READY);
      scheduler();
      RESTORE_CONTEXT();
   }
   ei();
}

int sem_get_value(sem_t sem)
{
   return sem.s_value;
}

void mutex_init(mutex_t *m)
{
   di();
   m->s_value            = 1;
   m->s_queue.pos_in     = 0;
   m->s_queue.pos_out    = 0;
   ei();   
}

void mutex_lock(mutex_t *m)
{
   di();
   m->s_value--;
   if (m->s_value < 0) {
      m->s_queue.blocked_queue[m->s_queue.pos_in] = READY_queue.pos_task_running;
      m->s_queue.pos_in = (m->s_queue.pos_in+1) % MAX_USER_TASKS;
      SAVE_CONTEXT(BLOCKED_SEM);
      scheduler();
      RESTORE_CONTEXT();
      ei();
   }
   ei();   
}

void mutex_unlock(mutex_t *m)
{
   di();
   m->s_value++;
   if (m->s_value <= 0) {
      change_task_state(m->s_queue.pos_out, READY);
      m->s_queue.pos_out = (m->s_queue.pos_out + 1) % MAX_USER_TASKS;
      SAVE_CONTEXT(READY);
      scheduler();
      RESTORE_CONTEXT();
      ei();
   }
   ei();   
}
