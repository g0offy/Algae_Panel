#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>



extern SemaphoreHandle_t xSerialSemaphore;

/**
 * @brief Set the up rtos tasks into the RTOS
 * 
 * @return true 
 * @return false 
 */
bool setup_rtos_tasks();


void TaskReadSensor(void *pvParameters);
void TaskPWM(void *pvParameters);




#endif