#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"

extern ready_queue_t READY_queue;

// Rotinas de inicialização
void os_init();
void hardware_init();
void kernel_start();

// Chamadas de sistema
void new_task(u_int id, u_int prioridade, task_ptr f);
void change_task_state(u_int pos_ready_queue, state_t new_state);
void task_delay(u_int time);
void task_delete(u_int pos_ready_queue);
void task_exit();

//u_int fila_cheia();

// Implementação do despachante
#define SAVE_CONTEXT(new_state) { \
do { \
    u_int pos_task = READY_queue.pos_task_running; \
    u_int task_stack_size = 0; \
    if (READY_queue.tasks[pos_task].task_state == RUNNING) { \
        READY_queue.tasks[pos_task].task_state  = new_state; \
        READY_queue.tasks[pos_task].BSR_reg     = BSR; \
        READY_queue.tasks[pos_task].STATUS_reg  = STATUS; \
        READY_queue.tasks[pos_task].W_reg       = WREG; \
        do { \
            READY_queue.tasks[pos_task].task_stack.stack[task_stack_size] = TOS; \
            task_stack_size += 1; \
            asm("POP"); \
        } while (STKPTR); \
        READY_queue.tasks[pos_task].task_stack.stack_size = task_stack_size; \
     } \
} while (0); \
} \

#define RESTORE_CONTEXT() { \
do { \
    u_int pos_task = READY_queue.pos_task_running; \
    READY_queue.tasks[pos_task].task_state = RUNNING; \
    BSR     = READY_queue.tasks[pos_task].BSR_reg; \
    STATUS  = READY_queue.tasks[pos_task].STATUS_reg; \
    WREG    = READY_queue.tasks[pos_task].W_reg; \
    STKPTR  = 0; \
    if (READY_queue.tasks[pos_task].task_stack.stack_size > 0) { \
        u_int task_stack_size = READY_queue.tasks[pos_task].task_stack.stack_size; \
        do { \
            asm("PUSH"); \
            task_stack_size -= 1; \
            TOS = READY_queue.tasks[pos_task].task_stack.stack[task_stack_size]; \
        } while (task_stack_size); \
    } \
    else { \
        asm("PUSH"); \
        TOS = READY_queue.tasks[pos_task].task_f; \
        READY_queue.tasks[pos_task].task_stack.stack_size = 1; \
    } \
    ei(); \
} while (0); \
} \

// Tratadores de interrupção
void __interrupt() isr_INT0();

#endif	/* KERNEL_H */

