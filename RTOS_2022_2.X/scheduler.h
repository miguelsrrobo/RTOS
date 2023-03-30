#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "types.h"

void scheduler();
// Round-Robin
u_int RR_scheduler();
// Prioridade
u_int PRIOR_scheduler();

u_int NO_PRE_scheduler();
u_int PRE_scheduler();

#endif	/* SCHEDULER_H */

