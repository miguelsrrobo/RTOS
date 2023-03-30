#include "kernel.h"
#include "scheduler.h"
#include "config_os.h"
#include "user_tasks.h"

// Declara fila de aptos
ready_queue_t READY_queue;

void os_init()
{
   READY_queue.ready_queue_size  = 0;
   READY_queue.pos_task_running  = 0;
   READY_queue.real_quantum      = RR_QUANTUM;
}

void hardware_init()
{
   #pragma config PBADEN = OFF
   // Configura interrupção zero
   INTCONbits.INT0IE    = 1;
   INTCONbits.INT0IF    = 0;
   INTCON2bits.RBPU     = 0; 
   INTCON2bits.INTEDG0  = 0;
   
   // Configuração do timer zero
   INTCONbits.TMR0IE = 1;
   INTCONbits.TMR0IF = 0;
   T0CONbits.T0CS    = 0;
   T0CONbits.T08BIT  = 1;
   T0CONbits.PSA     = 0;
   T0CONbits.T0PS    = 0b101;
   TMR0              = 64;
}

void kernel_start()
{
   // Ativa as interrupções globais
   ei();
   // Ativa o periférico de timer (timer zero)
   T0CONbits.TMR0ON = 1;
}

void new_task(u_int id, u_int prioridade, task_ptr f)
{
   tcb_t new_task;
   
   // Preenche os dados da nova tarefa
   new_task.task_id                 = id;
   new_task.task_prior              = prioridade;
   new_task.task_state              = READY;
   new_task.task_f                  = f;
   new_task.task_stack.stack_size   = 0;
   new_task.time_sleeping           = 0;
   
   // Insere a nova tarefa na fila de aptos
   READY_queue.tasks[READY_queue.ready_queue_size] = new_task;
   READY_queue.ready_queue_size += 1;
}

void change_task_state(u_int pos_ready_queue, state_t new_state)
{
   di();
   READY_queue.tasks[pos_ready_queue].task_state = new_state;
   ei();
}

void task_delay(u_int time)
{
   di();
   READY_queue.tasks[READY_queue.pos_task_running].time_sleeping = time;
   SAVE_CONTEXT(SLEEPING);
   scheduler();  
   RESTORE_CONTEXT();  

   ei();
}

void task_delete(u_int pos_ready_queue)
{
   change_task_state(pos_ready_queue, DELETED);
}

void task_exit()
{
   di();
   task_delete(READY_queue.pos_task_running);
   scheduler();
   RESTORE_CONTEXT();
   ei();
}


// Tratadores de interrupção
void __interrupt() isr_INT0()
{
   int i;
   if (INTCONbits.INT0IF) {
       new_task(4,10,aciona_led_4);       
       // Salva contexto da tarefa que está em execução
      SAVE_CONTEXT(READY);
      // Chama escalonador para colocar outra tarefa em execução
      scheduler();
      // Restaura o contexto da tarefa que irá entrar em execução
      RESTORE_CONTEXT();
      // Reseta o flag da interrupção zero
      INTCONbits.INT0IF = 0;
   }
   if (INTCONbits.TMR0IF) {
      // Decrementa o quantum
      READY_queue.real_quantum--;
      // Verifica se o quantum chegou a zero
      if (READY_queue.real_quantum == 0) {
         SAVE_CONTEXT(READY);
         // Chama escalonador para colocar outra tarefa em execução
         scheduler();
         // Restaura o contexto da tarefa que irá entrar em execução
         RESTORE_CONTEXT();         
         READY_queue.real_quantum = RR_QUANTUM;
      }
      // Verfica se tem tarefa em sleeping
      for (i = 0; i < READY_queue.ready_queue_size; i++) {
         if (READY_queue.tasks[i].time_sleeping > 0) {
            READY_queue.tasks[i].time_sleeping--;
            if (READY_queue.tasks[i].time_sleeping == 0) {
               READY_queue.tasks[i].task_state = READY;
            }
         }
      }
      TMR0 = 64;
      INTCONbits.TMR0IF = 0;
   }
}
