#include <rtos_tasks.h>




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial){;}
  if(xSerialSemaphore == NULL){
    xSerialSemaphore = xSemaphoreCreateMutex();
    if(xSerialSemaphore != NULL){
      xSemaphoreGive(xSerialSemaphore);
    }
  }

  setup_rtos_tasks();


}

void loop() {//! do not put anything here, task scheduler will take over
  }