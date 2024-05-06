
class MicroSwitch{
  public:
  MicroSwitch();
  MicroSwitch(int NO);
  bool get_state();

  private:
  int C;  // Common
  int NO; // Normally Open
  int NC; // Normally Closed
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


