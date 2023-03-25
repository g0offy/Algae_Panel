#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include <Arduino.h>
#include <LiquidCrystal.h>
// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only one Task is accessing this resource at any time.
SemaphoreHandle_t xSerialSemaphore;

// define two Tasks for DigitalRead & AnalogRead
void ReadJoystick( void *pvParameters );
void UpdateLCD( void *pvParameters );


enum Joystick_State{
  Up = 1,
  Down = -1,
  Centre = 0
};
int State_X = 0,State_Y=0;
// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  // Now set up two Tasks to run independently.
  xTaskCreate(
    ReadJoystick
    ,  "DigitalRead"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL ); //Task Handle

  xTaskCreate(
    UpdateLCD
    ,  "AnalogRead" // A name just for humans
    ,  128  // Stack size
    ,  NULL //Parameters for the task
    ,  1  // Priority
    ,  NULL ); //Task Handle

  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void ReadJoystick( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

  long last_millis = 0;
  // digital pin 2 has a pushbutton attached to it. Give it a name:
  uint8_t Button = 8;
  int xinput = A0, yinput = A1;
  Joystick_State prev_x_pos = Centre, prev_y_pos = Centre; 

  // make the pushbutton's pin an input:
  pinMode(Button, INPUT_PULLUP);
  pinMode(xinput,INPUT);
  pinMode(yinput,INPUT);


  while(1) // A Task shall never return or exit.
  {
    // read the input pin:
    int xPosition = analogRead(xinput);
    int yPosition = analogRead(yinput);
    int buttonState = digitalRead(Button);

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      // Serial.print(millis());
      // Serial.print(", time since previous task: ");
      // Serial.println(millis()-last_millis);
      // last_millis = millis();
      // Serial.print("X: ");
      // Serial.print(xPosition);
      // Serial.print(" | Y: ");
      // Serial.print(yPosition);
      // Serial.print(" | Button: ");
      // Serial.println(buttonState);
      
      if(xPosition>650&&prev_x_pos!=Joystick_State::Up){
        prev_x_pos=Up;
        State_X++;
        
      }
      if(xPosition<400&&prev_x_pos!=Joystick_State::Down){
        prev_x_pos=Down;
        State_X--;
        
      }
      if(xPosition>400&&xPosition<650){
        prev_x_pos=Joystick_State::Centre;
      }
      if(yPosition>650&&prev_y_pos!=Joystick_State::Up){
        State_Y++;
        prev_y_pos=Joystick_State::Up;
      }
      if(yPosition<400&&prev_y_pos!=Joystick_State::Down){
        State_Y--;
        prev_y_pos=Joystick_State::Down;
      }
      if(yPosition>400&&yPosition<650){
        prev_y_pos=Joystick_State::Centre;
      }
      Serial.print(" X_Pos: ");
      Serial.print(xPosition);
      Serial.print(" X_Joystick_State: ");
      Serial.print(prev_x_pos);
      Serial.print(" State_x: ");
      Serial.print(State_X);

      Serial.print(" Y_Pos: ");
      Serial.print(yPosition);
      Serial.print(" Y_Joystick_State: ");
      Serial.print(prev_y_pos);
      Serial.print("  State_y:");
      Serial.println(State_Y);
      

      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}

void UpdateLCD( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  long last_millis = 0;
  LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
  lcd.begin(16,2);

  while(1)
  {

    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      




      // Serial.print("Task 2: ");
      // Serial.print(millis());
      // Serial.print(", time since previous task: ");
      // Serial.println(millis()-last_millis);
      // last_millis = millis();

      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}