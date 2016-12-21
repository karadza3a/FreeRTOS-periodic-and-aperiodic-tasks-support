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

char* name1 = "1";
char* name2 = "2";
char* name3 = "3";

int main(void)
{
    vTaskPeriodicCreate( vExampleTask, name1, configMINIMAL_STACK_SIZE, name1, 3, NULL, 100);
    vTaskPeriodicCreate( vExampleTask, name2, configMINIMAL_STACK_SIZE, name2, 3, NULL, 150);
    vTaskPeriodicCreate( vExampleTask, name3, configMINIMAL_STACK_SIZE, name3, 4, NULL, 602);

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

void vApplicationIdleHook(){
    TickType_t currentTicks = xTaskGetTickCount();
    for(int i = 0; i<taskNUM_MAX_PERIODIC_TASKS; i++){
        if(xPeriodicTasks[i].pxTaskCode != NULL && (currentTicks % xPeriodicTasks[i].xPeriod == 0)){
            if (xPeriodicTasks[i].xLastRunAt != currentTicks) {
                xPeriodicTasks[i].xLastRunAt = currentTicks;
                    printf( ( char * ) "task %s created at %d\n" , xPeriodicTasks[i].pcName, currentTicks );
                    fflush( stdout );
                xTaskCreate(
                        xPeriodicTasks[i].pxTaskCode,
                        xPeriodicTasks[i].pcName,
                        xPeriodicTasks[i].usStackDepth,
                        xPeriodicTasks[i].pvParameters,
                        xPeriodicTasks[i].uxPriority,
                        xPeriodicTasks[i].pxCreatedTask
                );
            }
        }
    }
}