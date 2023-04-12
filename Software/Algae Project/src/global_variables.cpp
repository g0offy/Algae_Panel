#include <global_variables.h>

Variable::Variable(int _Variable,uint16_t _EE_Loc){
    var = _Variable;
    if(_EE_Loc<=E2END){
        EEPROM_LOC = _EE_Loc;
    }
}
Variable::Store(){
    if(EEPROM_LOC<0){
    return;
    }
    for(int i =0;i<sizeof(int);i++){
        EEPROM.update(EEPROM_LOC+i,*((uint8_t*)(&var)+i));
    }
}

Variable::Retrieve(){
    if(EEPROM_LOC<0){
        return;
    }
    var = 0;
    for(int i=0;i<sizeof(int);i++){
        var |= ((int)EEPROM.read(EEPROM_LOC+i)<<8*(sizeof(int)-i)); //! check if this is little or big endian
    }   
}

Variable::Reset(){
    var = default_var;
}

    //-----------------------------     Pin Definitions  ----------------------------------
int xinput = A0, yinput = A1;
int Button = 8;
    //-----------------------------     Global Objects Declarations  ----------------------------------
LiquidCrystal lcd = LiquidCrystal(2,3,4,5,6,7);


    //-----------------------------     EEPROM Variable Definitions  ----------------------------------

Variable dutycycle(50,1);
Variable autosave(10,5);