#include <Arduino.h>

const int pwm_pin = 3;
const float duty_cycle = 50;

void setup(){

pinMode(13,OUTPUT);
pinMode(pwm_pin,OUTPUT);

analogWrite(pwm_pin,255.0f*duty_cycle/100.0f);
}


void loop(){
    
    digitalWrite(LED_BUILTIN,1);
    delay(500.0f*duty_cycle/100.0f);//*duty_cycle/100
    digitalWrite(LED_BUILTIN,0);
    delay(500.0f*(1.0f-duty_cycle/100.0f));//

}