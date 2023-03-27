#include <global_variables.h>



    //-----------------------------     Pin Definitions  ----------------------------------
int xinput = A0, yinput = A1;
int Button = 8;
    //-----------------------------     Global Objects Declarations  ----------------------------------
LiquidCrystal lcd = LiquidCrystal(2,3,4,5,6,7);


    //-----------------------------     EEPROM Variable Definitions  ----------------------------------

Variable dutycycle(50,1);
Variable autosave(10,5);