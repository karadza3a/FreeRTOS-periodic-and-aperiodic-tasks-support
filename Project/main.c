#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*-----------------------------------------------------------*/

void vExampleTask(void *pvParameters){
    char* name = (char*) pvParameters;
    printf( ( char * ) " task %s, start - %u\n", name, ( unsigned int ) xTaskGetTickCount() );
    fflush( stdout );

    for(int i = 0; i<2000000; i++){
        volatile int j = sqrt(i*2*100);
    }
    printf( ( char * ) " task %s, end - %u\n", name, ( unsigned int ) xTaskGetTickCount() );
    fflush( stdout );

    vTaskDelete(NULL);
}

int main(void)
{
    vTaskPeriodicCreate( vExampleTask, "1", configMINIMAL_STACK_SIZE, "1", 3, NULL, 150);
    vTaskPeriodicCreate( vExampleTask, "2", configMINIMAL_STACK_SIZE, "2", 3, NULL, 100);
    vTaskPeriodicCreate( vExampleTask, "3", configMINIMAL_STACK_SIZE, "3", 3, NULL, 150);
    vTaskPeriodicCreate( vExampleTask, "4", configMINIMAL_STACK_SIZE, "4", 4, NULL, 602);

    vTaskStartScheduler();

    return 0;
}

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
    taskENTER_CRITICAL();
    {
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
    exit(-1);
}