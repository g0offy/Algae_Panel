#ifndef MENU_H
#define MENU_H
#include <UI_tests/Simple_Menu/SimpleMenu.h>
#include <LiquidCrystal.h>
#include <Arduino.h>
#include <global_variables.h>





    //-----------------------------     Menu Functions  ----------------------------------
void display(SimpleMenu *_menu);

void displayValue(SimpleMenu *_menu);

void Store();

void Retrieve();


#endif