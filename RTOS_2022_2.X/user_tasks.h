#ifndef USER_TASKS_H
#define	USER_TASKS_H

#include "kernel.h"
#include "types.h"

void user_config();

// Protótipo das funções da aplicação do usuário
TASK aciona_led_1();
TASK aciona_led_2();
TASK aciona_led_3();
TASK aciona_led_4();

#endif	/* USER_TASKS_H */

