#ifndef CONFIG_OS_H
#define	CONFIG_OS_H

#include "types.h"

// Número máximo de tarefas de usuário
#define MAX_USER_TASKS          5
#define MAX_STACK_SIZE          21
#define RR_QUANTUM              8

#define PRIOR_SCHEDULER         TRUE
#define RR_SCHEDULER            FALSE

#define NO_PRE_SCHEDULER         TRUE
#define PRE_SCHEDULER            FALSE


#endif	/* CONFIG_OS_H */

