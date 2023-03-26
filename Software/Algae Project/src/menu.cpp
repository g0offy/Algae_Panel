
#include <menu.h>

    SimpleMenu Joystick_Menu[3] = {
    SimpleMenu("Joystick X",&xinput),
    SimpleMenu("Joystick Y",&yinput),
    SimpleMenu("Button",&Button)
  };

  SimpleMenu PWM_Menu[1] = {
    SimpleMenu("Duty Cycle",&dutycycle.var,0,100)
  };
  SimpleMenu SD_Menu[1] = {
    SimpleMenu("autosave (min)",&autosave.var,1,1000)
  };

  SimpleMenu Menu[3] = {
    SimpleMenu("Joystick Options",3,Joystick_Menu),
    SimpleMenu("PWM Settings",1,PWM_Menu),
    SimpleMenu("SD Card Settings",1,SD_Menu)
  };

SimpleMenu TopMenu(3,Menu);


void display(SimpleMenu *_menu){
    lcd.clear();
    lcd.print(">");
    lcd.print(_menu->name);

    SimpleMenu *next = TopMenu.next();
    if(next != NULL){
        lcd.setCursor(1,1);
        lcd.print(next->name);
  }
}

void displayValue(SimpleMenu *_menu)
{
  lcd.clear();
  lcd.print(_menu->name);
  lcd.setCursor(0,1);
  lcd.print(_menu->getValue());
}


void Store(){

}