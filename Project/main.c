#include "FreeRTOS.h"
#include "task.h"
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
            xTaskAperiodicCreate(vATask, "aperiodic", configMINIMAL_STACK_SIZE, (void *const) xTaskGetTickCount(), NULL);
        }
    }

    vTaskDelete(NULL);
}

struct xTaskConfig{
    TickType_t xPeriod;
    TickType_t xLoad;
    UBaseType_t xPriority;
    char pcName[100];
} xTaskConfigs[20];

// https://wikimedia.org/api/rest_v1/media/math/render/svg/1c993bcea3acc65628cc14ced38bcd4de59a718e
void vCanBeScheduled(int n) {
    double sum = 0;
    double hypBound = 1;
    for (int i = 0; i < n; i++) {
        double u = xTaskConfigs[i].xLoad / (double) xTaskConfigs[i].xPeriod;
        sum += u;
        hypBound *= (u + 1);
    }
    double bound = n * (pow(2, 1 / (double) n) - 1);

    printf((char *) "\n      %f ?<= %f (%f ?<= 2)\n\n", sum, bound, hypBound);
    fflush(stdout);
}

void setPeriodicConfig(int i, UBaseType_t xPriority, TickType_t xPeriod, TickType_t xLoad) {
    xTaskConfigs[i] = (struct xTaskConfig){
            .xLoad = xLoad,
            .xPeriod = xPeriod,
            .xPriority = xPriority,
    };
    sprintf(xTaskConfigs[i].pcName, "periodic %d", i);
}

void setPollingSConfig(int i, UBaseType_t xPriority, TickType_t xPeriod, TickType_t xLoad) {
    configASSERT(i == 0);
    setPeriodicConfig(0, xPriority, xPeriod, xLoad);
    sprintf(xTaskConfigs[i].pcName, "polling_server");
}

int main(void) {
    /// server
    setPollingSConfig(0, 3, 120, 10);
    /// periodic tasks
    setPeriodicConfig(1, 3, 200, 25);
    setPeriodicConfig(2, 3, 100, 30);
    setPeriodicConfig(3, 3, 200, 20);
    setPeriodicConfig(4, 4, 405, 30);
    int n = 5;

    vCanBeScheduled(n);

    vInitializePollingServer(xTaskConfigs[0].xPriority, xTaskConfigs[0].xPeriod, xTaskConfigs[0].xLoad);
    for (int i = 1; i < n; i++) {
        vTaskPeriodicCreate(vExampleTask,
                            (const char *const) xTaskConfigs[i].pcName, configMINIMAL_STACK_SIZE,
                            (void *const) xTaskConfigs[i].xLoad,
                            xTaskConfigs[i].xPriority, NULL,
                            xTaskConfigs[i].xPeriod);
    }
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
