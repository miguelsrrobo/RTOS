#ifndef TYPES_H
#define	TYPES_H

#include "config_os.h"
#include <xc.h>

#define TRUE    1
#define FALSE   0

typedef unsigned int u_int;
typedef char byte;
typedef void (*task_ptr)();
typedef void TASK;

typedef enum {READY, RUNNING, WAITING, SLEEPING, DELETED, BLOCKED_SEM} state_t;

typedef struct stack_data {
    uint24_t stack[MAX_STACK_SIZE];
    u_int stack_size;    
} stack_data_t;

typedef struct tcb {
    u_int task_id;
    u_int task_prior;
    state_t task_state;
    task_ptr task_f;
    stack_data_t task_stack;
    uint24_t BSR_reg;
    uint24_t STATUS_reg;
    uint24_t W_reg;
    u_int time_sleeping;
} tcb_t;

typedef struct ready_queue {
    tcb_t tasks[MAX_USER_TASKS];
    u_int ready_queue_size;
    u_int pos_task_running;
    u_int real_quantum;
} ready_queue_t;

typedef struct sem_queue {
    u_int blocked_queue[MAX_USER_TASKS];
    u_int pos_in;
    u_int pos_out;
} sem_queue_t;

typedef struct sem {
    int s_value;
    sem_queue_t s_queue;
} sem_t;

typedef struct sem mutex_t;

#endif	/* TYPES_H */

