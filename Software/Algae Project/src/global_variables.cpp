#include <global_variables.h>

EEPROM_Variable::EEPROM_Variable(int _Variable,uint8_t _EE_Loc,EEPROM_Manager* _Manager)
    :default_var(_Variable)
{
    var = _Variable;
    if(_EE_Loc<=E2END){ // check if location is within memory.
        EEPROM_LOC = _EE_Loc;
    }
    if(_Manager!=NULL){ // add this EEPROM variable to the EEPROM manager
        _Manager->Add(this,_EE_Loc);
    }

}
void EEPROM_Variable::Store(){
    if(EEPROM_LOC<0){
    return;
    }
    for(size_t i =0;i<sizeof(int);i++){
        EEPROM.update(EEPROM_LOC*4+i,*((uint8_t*)(&var)+i));
    }
}

void EEPROM_Variable::Retrieve(){
    if(EEPROM_LOC<0){
        return;
    }
    var = 0;
    for(size_t i=0;i<sizeof(int);i++){
        var |= ((int)EEPROM.read(EEPROM_LOC*4+i)<<8*(sizeof(int)-i)); //! check if this is little or big endian
    }   
}

void EEPROM_Variable::Reset(){
    var = default_var;
}


    EEPROM_Manager::EEPROM_Manager(){

    }


    void EEPROM_Manager::Store(){
        for(size_t i=0; i < this->size();i++){
            this->at(i)->Store();
        }
    }

    void EEPROM_Manager::Retrieve(){
        for(size_t i=0; i < this->size();i++){
            this->at(i)->Retrieve();
        }
    }

    void EEPROM_Manager::Reset(){
        for(size_t i=0; i < this->size();i++){
            this->at(i)->Reset();
        }
    }

    bool EEPROM_Manager::Add(EEPROM_Variable* variable,uint8_t EEPROM_LOC){
        if(EEPROM_MAP & (1U << EEPROM_LOC) ){ // if the EEPROM memory location is already taken then return false 
            EEPROM_errors.push_back(EEPROM_LOC);
            return(false);
        }
        EEPROM_MAP |= (1U << EEPROM_LOC);
        this->push_back(variable);
        return(true);
    }

    void EEPROM_Manager::serial_errors(){
        Serial.print("Multiple Variables were initialised at locations: \n");
        for(size_t i=0;i<EEPROM_errors.size();i++){
            Serial.print(EEPROM_errors.at(i));
            Serial.print("\n");

        }
    }





    //-----------------------------     Pin Definitions  ----------------------------------
int xinput = A0, yinput = A1;
int Button = 8;
    //-----------------------------     Global Objects Declarations  ----------------------------------
LiquidCrystal lcd = LiquidCrystal(2,3,4,5,6,7);


    //-----------------------------     EEPROM Variable Definitions  ----------------------------------
EEPROM_Manager rom_manager;
EEPROM_Variable dutycycle(50,1,&rom_manager);
EEPROM_Variable autosave(10,2,&rom_manager);