#ifndef SYNC_H
#define	SYNC_H

#include "types.h"

// Chamadas de sistema para o semáforo
void sem_init(sem_t *sem, u_int value);
void sem_wait(sem_t *sem);
void sem_post(sem_t *sem);
int sem_get_value(sem_t sem);

// Chamadas de sistema para variáveis mutex
void mutex_init(mutex_t *m);
void mutex_lock(mutex_t *m);
void mutex_unlock(mutex_t *m);

#endif	/* SYNC_H */

