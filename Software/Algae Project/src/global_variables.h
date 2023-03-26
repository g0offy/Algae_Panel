#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <UI_tests/Simple_Menu/SimpleMenu.h>
#include <EEPROM.h>
/**
 * @brief Class for editing variables when part of the simple menu structure
 * 
 */

class Variable {
    public:
        Variable(int _Variable, int _Increment, int _min, int _max){
            var = _Variable;
            delta = _Increment;
        }
        /**
         * @brief 
         *  _min minimum value the internal increment/decrement functions will allow
         *  _max maximum value the internal increment/decrement functions will allow
         * _EE_Loc location in EEPROM memmory where this value is to be stored must be < 1024 (max size2)
         */
        Variable(int _Variable, int _Increment, int _min, int _max,uint16_t _EE_Loc){
            var = _Variable;
            delta = _Increment;
            if(_EE_Loc<=E2END){
                EEPROM_LOC = _EE_Loc;
            }
        }
        void Increment(){
            if(var+delta>max){ // this is incase of someone putting a negative min
                var = max;
                return;
            }
            if(var+delta<min){
                var = min;
                return;
            }
            var = var+delta;
            return;
        }
        void Decrement(){
            if(var-delta>max){
                var = max;
                return;
            }
            if(var-delta<min){
                var = min;
                return;
            }
            var = var-delta;
        }
        void Store(){ //saves value to eprom for a later time
            if(sizeof(int)<=EEPROM_LOC){
                for(int i =0;i<sizeof(int);i++){
                    EEPROM.update(EEPROM_LOC+i,*((uint8_t*)(&var)+i));
                }
            }
        }
        void Retrieve(){
            if(sizeof(int)<=EEPROM_LOC){
                var = 0;
                for(int i=0;i<sizeof(int);i++){
                    var |= ((int)EEPROM.read(EEPROM_LOC+i)<<8*(sizeof(int)-i)); //! check if this is little or big endian
                }
            }
        }

        int var;
    private:

        int delta;
        int min;
        int max;
        uint16_t EEPROM_LOC=-1;
};


// PINS //
extern int xinput, yinput;
extern int Button;

extern LiquidCrystal lcd;

// EEPROM Variables //! move to eeprom later so they're kept between power offs
extern SimpleMenu TopMenu;

extern Variable dutycycle ;


#endif