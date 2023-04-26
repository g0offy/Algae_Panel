
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

  DS18B20 TempSensor1(TSensorPin1);
  DS18B20 TempSensor2(TSensorPin2);
  NewPing Sonar1(SSensorPin1,SonarEchoPin,400);
  NewPing Sonar2(SSensorPin2,SonarEchoPin,400);

  while(1){ // add stuff here to add it to the task
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t) 5)==pdTRUE){ // this checks if we can get the mutex semaphore
      // Serial.write("PWM has control over Serial port\n");
      // Temp1 = TempSensor1.readTempC();
      // Temp2 = TempSensor2.readTempC();
      SonarDist1 = Sonar1.ping_cm();
      SonarDist2 = Sonar2.ping_cm();
      
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
  int xPosition = 0, yPosition = 0, buttonState = 0;

  while(1){ // add stuff here to add it to the task
    if(xSemaphoreTake(xSerialSemaphore,(TickType_t) 5)==pdTRUE){ // this checks if we can get the mutex semaphore
      // Serial.write("PWM has control over Serial port\n");
      xPosition = analogRead(xinput)-1024/2;
      yPosition = analogRead(yinput)-1024/2;
      buttonState = digitalRead(Button);
      if((abs(xPosition)>256||abs(yPosition)>256)){// create deadzone to minimise false positive inputs
        if(prev_pos==Centre){ // requires the joystick to be returned to centre before reading again.
          if(abs(xPosition)>abs(yPosition)){ // remove diagonal functionality
            
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
      xSemaphoreGive(xSerialSemaphore);
    }
    vTaskDelay(1);
  }}
  

  