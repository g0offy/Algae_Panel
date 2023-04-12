#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <UI_tests/Simple_Menu/SimpleMenu.h>
#include <EEPROM.h>


/**
 * @brief Class for for saving and editing to EEPROM
 * 
 */
class Variable {
    public:
        Variable(int _Variable)
        :default_var(_Variable)
        {
            var = _Variable;

        }
        /**
         * @brief 
         * _EE_Loc location in EEPROM memmory where this value is to be stored must be < 1024 (max size2)
         */
        Variable(int _Variable,uint16_t _EE_Loc);
        /**
         * @brief Stores Value to EEPROM, should be called by the user, because EEPROM only has 100,000 writes
         * 
         */
        void Store();

        /**
         * @brief Retrieves Value from EEPROM, should be done on startup.
         * 
         */
        void Retrieve();

        /**
         * @brief sets the variable var to the default var
         * 
         */
        void Reset();

        /**
         * @brief integer variable in question
         * 
         */
        int var;
        
    private:
        /**
         * @brief Location of this variable in EEPROM
         * 
         */
        uint16_t EEPROM_LOC=-1;
        /**
         * @brief var is set to this in the case of a hard reset call.
         * 
         */
        const int default_var;
};





    //-----------------------------     Pin Declarations  ----------------------------------
extern int xinput, yinput;
extern int Button;
    //-----------------------------     Global Objects Declarations  ----------------------------------
extern LiquidCrystal lcd;

    //-----------------------------     EEPROM Variable Declarations  ----------------------------------
extern SimpleMenu TopMenu;

extern Variable dutycycle ;
extern Variable autosave ;


    //-----------------------------     Other Stuff  ----------------------------------
enum Joystick_State{
  Up = 1,
  Down = 2,
  left =-1,
  right = -2,
  Centre = 0
};


#endif