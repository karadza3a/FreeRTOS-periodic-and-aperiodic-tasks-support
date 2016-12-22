#include "FreeRTOS.h"
#include "task.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*-----------------------------------------------------------*/

void vATask(void *pvParameters) {
    int sch = (int) pvParameters;
//    printf((char *) " ap start (sch %d) - %u\n", sch, (unsigned int) xTaskGetTickCount());
//    fflush(stdout);

    for (int i = 0; i < 1000000; i++) {
        volatile int j = (volatile int) sqrt(i / 2 * 100);
    }

//    printf((char *) " ap stop (sch %d) - %u\n", sch, (unsigned int) xTaskGetTickCount());
//    fflush(stdout);

    vTaskDelete(NULL);
}

void vExampleTask(void *pvParameters) {
    TickType_t load = (TickType_t) pvParameters;
    BaseType_t n = load*48000;

    for (int i = 0; i < n; i++) {
        volatile int j = (volatile int) sqrt(i % 10 * 10000);
        int r = rand();    //returns a pseudo-random integer between 0 and RAND_MAX
        if (r % 10000000 == 7) {
//            printf((char *) "ap-sch-at%d\n", xTaskGetTickCount());
//            fflush(stdout);
            xTaskAperiodicCreate(vATask, "ap", configMINIMAL_STACK_SIZE, (void *const) xTaskGetTickCount(), NULL);
        }
    }

    vTaskDelete(NULL);
}

int main(void) {
    /// server
    setPollingSConfig(0, 3, 120, 10);
    /// periodic tasks
    setPeriodicConfig(1, 3, 200, 25, vExampleTask);
    setPeriodicConfig(2, 3, 100, 30, vExampleTask);
    setPeriodicConfig(3, 3, 200, 20, vExampleTask);
    setPeriodicConfig(4, 4, 405, 30, vExampleTask);

    vCanBeScheduled(xTaskConfigsN);
    vTaskStartScheduler();

    return 0;
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName) {
    taskENTER_CRITICAL();
    {
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
    exit(-1);
}

void vApplicationIdleHook(){
    vSystemIdleHook();
}

int vPrintf(const char *format, ...) {
    va_list args;
    va_start (args, format);
    int x = vprintf(format, args);
    va_end (args);
    return x;
}
