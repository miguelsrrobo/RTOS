#include "user_tasks.h"
#include "sync.h"

sem_t s;

void user_config()
{
   TRISDbits.RD0 = 0;
   TRISDbits.RD1 = 0;
   TRISDbits.RD2 = 0;
   
   asm("GLOBAL _aciona_led_1, _aciona_led_2, _aciona_led_3, _aciona_led_4");
   sem_init(&s, 0);
}

// Protótipo das funções da aplicação do usuário
TASK aciona_led_1()
{
   while (1) {      
      LATDbits.LATD0 = ~PORTDbits.RD0;
   }
}

TASK aciona_led_2()
{
   //task_delete(2);
   while (1) {
      //sem_wait(&s);
      LATDbits.LATD1 = ~PORTDbits.RD1;
   }   
}

TASK aciona_led_3()
{
   while (1) {
      LATDbits.LATD2 = ~PORTDbits.RD2;
      task_delay(50);
      //sem_post(&s);
   }   
}

TASK aciona_led_4()
{
   while (1) {
      LATDbits.LATD2 = ~PORTDbits.RD2;
      task_delay(50);
      //sem_post(&s);
   }   
}