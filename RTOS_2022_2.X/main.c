#include <xc.h>
#include "kernel.h"
#include "user_tasks.h"

int main()
{
   // Inicializar as estruturas de dados do SO
   os_init();
   
   // Inicializo o hardware
   hardware_init();
   
   // Configura aplicação do usuário
   user_config();
   
   // Cria tarefas do usuário
   new_task(1, 5, aciona_led_1);
   new_task(2, 5, aciona_led_2);
   new_task(3, 5, aciona_led_3);
   
   // Inicializa o kernel do SO
   kernel_start();
   
   while (1);
   
   return 0;
}
