#include "motor.h"

class Claw{
  public:
  open();
  close();

  private:

  
};

MicroSwitch::MicroSwitch() {}

MicroSwitch::MicroSwitch(int NO) {
  this->NO = NO;
}

bool MicroSwitch::get_state() {
  // if the switch is pressed, return 1
  // otherwise return 0
  return !digitalRead(NO);
  // return 0;
}


