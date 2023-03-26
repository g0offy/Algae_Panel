
#include <menu.h>


SimpleMenu Contruct_menu(){


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


    SimpleMenu TopLevelMenu(2,Menu);
    return(TopLevelMenu);
}

// SimpleMenu TopMenu = Contruct_menu();

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