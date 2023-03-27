#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <UI_tests/Simple_Menu/SimpleMenu.h>
#include <LiquidCrystal.h>
#include <menu.h>


    //-----------------------------     RTOS Variables Declarations ----------------------------------
extern SemaphoreHandle_t xSerialSemaphore;
extern SemaphoreHandle_t xSDSemaphore;




/**
 * @brief Set the up rtos tasks into the RTOS
 * 
 * @return true 
 * @return false 
 */
bool setup_rtos_tasks();


    //-----------------------------     RTOS Task Declarations  ----------------------------------
/**
 * @brief rtos task reads and updates sensor values 
 * 
 * @param pvParameters 
 */
void TaskReadSensor(void *pvParameters);
/**
 * @brief controls pwm signal to pump
 * 
 * @param pvParameters 
 */
void TaskPWM(void *pvParameters);

/**
 * @brief saves data to sd card for later reading
 * 
 * @param pvParameters 
 */
void TaskSD(void *pvParameters);

/**
 * @brief Reads User input and updates the display to match
 * 
 * @param pvParameters 
 */
void TaskUI(void *pvParameters);




#endif