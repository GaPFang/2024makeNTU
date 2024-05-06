// const int xPin = 0;  //X軸 接類比A0
// const int yPin = 1;  //Y軸 接類比A1
// const int zPin = 2;  //Z軸 接類比A2
// const int motor_radius=255;

class Joystick{
  public:
  Joystick();
  Joystick(int xPin, int yPin);
  Joystick(int xPin, int yPin, int zPin);
  int get_x();
  int get_y();
  int calculate_motor_x();
  int calculate_motor_y();

  private:
  int xPin;
  int yPin;
  int zPin;
};

Joystick::Joystick() {}

Joystick::Joystick(int xPin, int yPin) {
  this->xPin = xPin;
  this->yPin = yPin;
}

Joystick::Joystick(int xPin, int yPin, int zPin) {
  this->xPin = xPin;
  this->yPin = yPin;
  this->zPin = zPin;
}

int Joystick::get_x(){
  return analogRead(xPin);
}

int Joystick::get_y(){
  return analogRead(yPin);
}

int Joystick::calculate_motor_x(){
  int tmp = (get_x() - 523)/2.2;
  //int tmp = (get_x() - 523)/2;
  if(tmp > 250) return 250;
  else if(tmp < -250) return -250;
  else return tmp;
}

int Joystick::calculate_motor_y(){
  int tmp = (get_y() - 542)/2.2;
  //int tmp =  (get_y() - 542)/2;
  if(tmp > 250) return 250;
  else if(tmp < -250) return -250;
  else return tmp;
}

