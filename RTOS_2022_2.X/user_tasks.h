#ifndef USER_TASKS_H
#define	USER_TASKS_H

#include "kernel.h"
#include "types.h"

void user_config();

// Prot�tipo das fun��es da aplica��o do usu�rio
TASK aciona_led_1();
TASK aciona_led_2();
TASK aciona_led_3();
TASK aciona_led_4();

#endif	/* USER_TASKS_H */

