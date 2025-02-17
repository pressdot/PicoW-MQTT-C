#include "FreeRTOS.h"
#include <stdio.h>
#include <task.h>
/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
//Adjusted to the latest FreeRTOS Release
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize,BaseType_t xCoreId )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
  	static StaticTask_t xIdleTaskTCBs[ configNUMBER_OF_CORES ];
	static StackType_t uxIdleTaskStacks[ configNUMBER_OF_CORES ][ configMINIMAL_STACK_SIZE ];
	*ppxIdleTaskTCBBuffer = &( xIdleTaskTCBs[ xCoreId ] );
	*ppxIdleTaskStackBuffer = &( uxIdleTaskStacks[ xCoreId ][ 0 ] );
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task’s state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task’s stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}


void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                      char *pcTaskName ){
	printf("----------------------------------------------\n");
	printf("STACK OVERFLOW on %s\n", pcTaskName);
	printf("----------------------------------------------\n");
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vAssertCalled( const char *pcFile, uint32_t ulLine ){
	printf("----------------------------------------------\n");
	printf("ASSERT FAILED %s line: %d\n", pcFile, ulLine);
	printf("----------------------------------------------\n");
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
