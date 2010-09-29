#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <stm32f10x.h>
#include "FreeRTOS.h"
#include "task.h"  
#include "queue.h" 
#include "semphr.h"

#ifdef USART2_ENABLED
static void prvUsartTestTask( void *pvparameters );
#endif


int main(void)
{

#ifdef USART2_ENABLED
  usart2_init();
  xTaskCreate( prvUsartTestTask, ( signed char * ) "USART2Test", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY + 1, NULL);
#endif
  vTaskStartScheduler();
  for(;;);
}


void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	( void ) pxTask;                                                                                                                                              
	( void ) pcTaskName;                                                                                                                                                                       
	for( ;; );                                                                                                                                                      
}                                                                                                                                                                       

void vApplicationTickHook( void )
{

}                                                                                                                                      

#ifdef USART2_ENABLED
static void prvUsartTestTask( void *pvparameters )
{
  uint8_t buffer[8];

  for(;;)
    {
      size_t n = usart2_read(buffer, sizeof(buffer));
      usart2_write(buffer, n);
    }

}
#endif
