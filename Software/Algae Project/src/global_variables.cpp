#include <global_variables.h>
int xinput = A0, yinput = A1;
int Button = 8;

LiquidCrystal lcd = LiquidCrystal(2,3,4,5,6,7);

// EEPROM Variables //! move to eeprom later so they're kept between power offs
// int * blank;
    SimpleMenu Joystick_Menu[3] = {
    SimpleMenu("Joystick X",&xinput),
    SimpleMenu("Joystick Y",&yinput),
    SimpleMenu("Button",&Button)
  };
  SimpleMenu PWM_Menu[1] = {
    SimpleMenu("Duty Cycle:", &dutycycle)
  };

  SimpleMenu Menu[2] = {
    SimpleMenu("Joystick Options",3,Joystick_Menu),
    SimpleMenu("PWM Settings",1,PWM_Menu)
  };


    SimpleMenu TopMenu(2,Menu);
// SimpleMenu TopMenu("blank",blank);
// SimpleMenu* TopMenu = NULL;
int dutycycle = 25;

