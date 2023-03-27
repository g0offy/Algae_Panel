
#include <rtos_tasks.h>
#include <global_variables.h>

    //-----------------------------     RTOS Variable Definitions  ----------------------------------

SemaphoreHandle_t xSerialSemaphore;
  
  



  
  













bool setup_rtos_tasks(){


  if(xTaskCreate(
    TaskUI,
    "UI",
    128,
    NULL,
    2,
    NULL
  )!=pdPASS){
    return(false);
  }
  // if(xTaskCreate(
  //   TaskPWM,
  //   "WritePWM",
  //   128,
  //   NULL,
  //   3,
  //   NULL
  // )!=pdPASS){
  //   return(false);
  // }
  //   if(xTaskCreate(
  //   TaskSD,
  //   "WriteSD",
  //   128,
  //   NULL,
  //   1,
  //   NULL
  // )!=pdPASS){
  //   return(false);
  // }


return(true);
}

    //-----------------------------     RTOS Task Definition  ----------------------------------


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




void TaskUI(void *pvParameters){
//run setup, this is done once

  Joystick_State prev_pos = Centre; 
  // make the pushbutton's pin an input:
  pinMode(Button, INPUT_PULLUP);
  pinMode(xinput,INPUT);
  pinMode(yinput,INPUT);

  lcd.begin(16,2);
  TopMenu.begin(display,displayValue);

  while(1){ // add stuff here to add it to the task
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t) 5)==pdTRUE){ // this checks if we can get the mutex semaphore
      // Serial.write("PWM has control over Serial port\n");
      int xPosition = analogRead(xinput)-1024/2;
      int yPosition = analogRead(yinput)-1024/2;
      int buttonState = digitalRead(Button);
      if((abs(xPosition)>256||abs(yPosition)>256)){
        if(prev_pos==Centre){
          if(abs(xPosition)>abs(yPosition)){
            
            if(xPosition>0){
              prev_pos=Joystick_State::Up;
              TopMenu.up();
            }
            else{
              prev_pos=Joystick_State::Down;
              TopMenu.down();
            }
          }
          else{
            if(yPosition>0){
              prev_pos=Joystick_State::Up;
              TopMenu.select();
            }
            else{
              prev_pos=Joystick_State::Down;
              TopMenu.back();
            }

          }


        }
      }
      else{
        prev_pos=Centre;
      }
      // Serial.print(millis());
      // Serial.print("X: ");
      // Serial.print(xPosition);
      // Serial.print(" | Y: ");
      // Serial.print(yPosition);
      // Serial.print(" | Button: ");
      // Serial.println(buttonState);
      xSemaphoreGive(xSerialSemaphore);
    }
    vTaskDelay(1);
  }}
  

  