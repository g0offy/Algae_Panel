
#include <rtos_tasks.h>


SemaphoreHandle_t xSerialSemaphore;


#define SETUP_TASK()

bool setup_rtos_tasks(){


  if(xTaskCreate(
    TaskReadSensor,
    "ReadSensor",
    128,
    NULL,
    2,
    NULL
  )!=pdPASS){
    return(false);
  }
  if(xTaskCreate(
    TaskPWM,
    "WritePWM",
    128,
    NULL,
    3,
    NULL
  )!=pdPASS){
    return(false);
  }
    if(xTaskCreate(
    TaskSD,
    "WriteSD",
    128,
    NULL,
    1,
    NULL
  )!=pdPASS){
    return(false);
  }


return(true);
}


void TaskReadSensor(void *pvParameters){
//run setup, this is done once

  while(1){ // add stuff here to add it to the task
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t) 5)==pdTRUE){ // this checks if we can get the mutex semaphore
      // Serial.write("PWM has control over Serial port\n");
      




      xSemaphoreGive(xSerialSemaphore);
    }





    vTaskDelay(1);
  }}

void TaskPWM(void *pvParameters){
//run setup here this is done once



  while(1){// add stuff here to add it to the task
    
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t) 5)==pdTRUE){ // this checks if we can get the mutex semaphore
      // Serial.write("PWM has control over Serial port\n");
      




      xSemaphoreGive(xSerialSemaphore);
    }





    vTaskDelay(1);
  }}


  void TaskSD(void *pvParameters){


  while(1){// add stuff here to add it to the task
    
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t) 5)==pdTRUE){ // this checks if we can get the mutex semaphore
      // Serial.write("PWM has control over Serial port\n");
      




      xSemaphoreGive(xSerialSemaphore);
    }





    vTaskDelay(1);
  }}

  