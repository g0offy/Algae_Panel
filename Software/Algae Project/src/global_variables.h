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
class Variable { //! This is all here because it was a templated class before and i cant be fucked to move the definitions to the .cpp file, do it yourself
    public:
        Variable(int _Variable){
            var = _Variable;

        }
        /**
         * @brief 
         * _EE_Loc location in EEPROM memmory where this value is to be stored must be < 1024 (max size2)
         */
        Variable(int _Variable,uint16_t _EE_Loc){
            var = _Variable;
            if(_EE_Loc<=E2END){
                EEPROM_LOC = _EE_Loc;
            }
        }
        /**
         * @brief Stores Value to EEPROM, should be called by the user, because EEPROM only has 100,000 writes
         * 
         */
        void Store(){ //saves value to eprom for a later time
            if(EEPROM_LOC<0){
                return;
            }
            for(int i =0;i<sizeof(int);i++){
                EEPROM.update(EEPROM_LOC+i,*((uint8_t*)(&var)+i));
            }
        }
        /**
         * @brief Retrieves Value from EEPROM, should be done on startup.
         * 
         */
        void Retrieve(){
            if(EEPROM_LOC<0){
                return;
            }
            var = 0;
            for(int i=0;i<sizeof(int);i++){
                var |= ((int)EEPROM.read(EEPROM_LOC+i)<<8*(sizeof(int)-i)); //! check if this is little or big endian
            }
        }
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