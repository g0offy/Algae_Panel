#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <UI_tests/Simple_Menu/SimpleMenu.h>


// PINS //
extern int xinput, yinput;
extern int Button;

extern LiquidCrystal lcd;

// EEPROM Variables //! move to eeprom later so they're kept between power offs
extern SimpleMenu TopMenu;

extern int dutycycle ;


#endif