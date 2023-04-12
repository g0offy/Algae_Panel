// Include Libraries
#include "BH1750.h"
#include "Wire.h"
#include "Arduino.h"
#include "DS18B20.h"
#include "Relay.h"
#include "SolenoidValve.h"
#include "Wire.h"
#include "BH1750.h"
#include "dht.h"
#include "SPI.h"
#include "SD.h"

BH1750 bh1750_a;
BH1750 bh1750_b;
dht DHT;
File sdcard_file;

// Pin Definitions
#define DHT22_PIN 8
#define DS18B20WP_1_PIN_DQ  3
#define DS18B20WP_2_PIN_DQ  9
#define RELAYMODULE_PIN_SIGNAL  6
#define SOLENOIDVALVE_PIN_COIL1 5
int x = 0;

// object initialization
DS18B20 ds18b20wp_1(DS18B20WP_1_PIN_DQ);
DS18B20 ds18b20wp_2(DS18B20WP_2_PIN_DQ);
Relay relayModule(RELAYMODULE_PIN_SIGNAL);
SolenoidValve solenoidValve(SOLENOIDVALVE_PIN_COIL1);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  bh1750_a.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
  bh1750_b.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5C, &Wire);
   if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  Serial.print("Date  ");   
  Serial.print("      ");
  Serial.print("   Time  ");
  Serial.print("     ");
  Serial.print("   Temp   ");
  Serial.println("     ");
  sdcard_file = SD.open("data.txt", FILE_WRITE);
  if (sdcard_file) { 
    sdcard_file.print("Date  ");   
    sdcard_file.print("      ");
    sdcard_file.print("   Time  ");
    sdcard_file.print("     ");
    sdcard_file.print("   Temp   ");
    sdcard_file.println("     ");
    sdcard_file.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
}

void loop() {
  x = x + 1;
  Serial.println(x); 
  int i = 200;
  float light_level_a = bh1750_a.readLightLevel();
  float light_level_b = bh1750_b.readLightLevel();
  Serial.print("Light: ");
  Serial.print(light_level_a);
  Serial.println(" lx");
  delay(i);
  Serial.print("Light: ");
  Serial.print(light_level_b);
  Serial.println(" lx");
  delay(i);
  int chk = DHT.read22(DHT22_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(i);
  float ds18b20wp_1TempC = ds18b20wp_1.readTempC();
  Serial.print(F("Temp: ")); Serial.print(ds18b20wp_1TempC); Serial.println(F(" [C]"));
  delay(i);
  float ds18b20wp_2TempC = ds18b20wp_2.readTempC();
  Serial.print(F("Temp: ")); Serial.print(ds18b20wp_2TempC); Serial.println(F(" [C]"));
  delay(i);
  sdcard_file = SD.open("data.txt", FILE_WRITE);
  if (sdcard_file) {
    sdcard_file.println(x);    
    sdcard_file.println(bh1750_a.readLightLevel());
    sdcard_file.println(bh1750_b.readLightLevel());
    sdcard_file.println(DHT.temperature);
    sdcard_file.println(DHT.humidity);
    sdcard_file.println(ds18b20wp_1TempC);
    sdcard_file.println(ds18b20wp_2TempC);
    sdcard_file.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  
  if (light_level_a > 10000 || light_level_b>10000) {
    relayModule.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    relayModule.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    delay(200);
    solenoidValve.on(); // 1. turns on
    delay(500);       // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    solenoidValve.off();// 3. turns off
    delay(500);       // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    delay(10000);
  }
  
   else {
   delay(200);
   }
}
