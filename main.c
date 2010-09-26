#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <stm32f10x.h>
#include "FreeRTOS.h"
#include "task.h"  
#include "queue.h" 
#include "semphr.h"

int main(void)
{
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

