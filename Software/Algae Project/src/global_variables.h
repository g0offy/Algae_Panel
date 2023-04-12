#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <UI_tests/Simple_Menu/SimpleMenu.h>
#include <EEPROM.h>
#include <ArduinoSTL.h>

class EEPROM_Manager;
/**
 * @brief Class for for saving and editing to EEPROM
 * 
 */
class EEPROM_Variable {
    public:
        EEPROM_Variable(int _Variable)
        :default_var(_Variable)
        {
            var = _Variable;
            

        }
        /**
         * @brief 
         * _EE_Loc location in EEPROM memmory where this value is to be stored must be < 1024 (max size2)
         */
        EEPROM_Variable(int _Variable,uint8_t _EE_Loc,EEPROM_Manager* _Manager);
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


class EEPROM_Manager : private std::vector<EEPROM_Variable*> {

    public:
        EEPROM_Manager();

        void Store();

        void Retrieve();

        void Reset();

        bool Add(EEPROM_Variable* variable,uint8_t EEPROM_LOC);


        void serial_errors();

        

        uint8_t EEPROM_MAP;
        
        std::vector<uint8_t> EEPROM_errors;
};





    //-----------------------------     Pin Declarations  ----------------------------------
extern int xinput, yinput;
extern int Button;
    //-----------------------------     Global Objects Declarations  ----------------------------------
extern LiquidCrystal lcd;

    //-----------------------------     EEPROM Variable Declarations  ----------------------------------
extern SimpleMenu TopMenu;

extern EEPROM_Manager rom_manager;

extern EEPROM_Variable dutycycle ;
extern EEPROM_Variable autosave ;


    //-----------------------------     Other Stuff  ----------------------------------
enum Joystick_State{
  Up = 1,
  Down = 2,
  left =-1,
  right = -2,
  Centre = 0
};


#endif