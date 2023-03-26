#include <global_variables.h>




int xinput = A0, yinput = A1;
int Button = 8;

LiquidCrystal lcd = LiquidCrystal(2,3,4,5,6,7);

// EEPROM Variables //! move to eeprom later so they're kept between power offs
// int * blank;



//     
// SimpleMenu TopMenu("blank",blank);
// SimpleMenu* TopMenu = NULL;
Variable dutycycle(50,10,0,100);

