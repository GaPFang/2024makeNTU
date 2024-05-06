#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
  int IN1;
  int IN2;
  int PWM;
  public:
  Motor();
  Motor(int input1, int input2, int inputPWM);
  void motor_set_pin(int input1, int input2);
  void motor_set_PWM(int inputPWM);
  void motor_write(int v);
  void motor_stop();
};

Motor::Motor() {}

Motor::Motor(int input1, int input2, int inputPWM) {
  this->IN1 = input1;
  this->IN2 = input2;
  this->PWM = inputPWM;
}

void Motor::motor_set_pin(int input1, int input2) {
  this->IN1 = input1;
  this->IN2 = input2;
  return;
}

void Motor::motor_set_PWM(int inputPWM) {
  this->PWM = inputPWM;
  return;
}

void Motor::motor_write(int v) {
  /*Serial.println(vL);
  Serial.println(vR);*/
  if(v > 0)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else
  {
    digitalWrite(IN2, HIGH);
    digitalWrite(IN1, LOW);
    v = -v;
  }

  

  analogWrite(PWM, v);
  return;
}

void Motor::motor_stop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}

#endif