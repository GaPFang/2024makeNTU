#include "motor.h"
#include "joystick.h"
#include "microswitch.h"
#include <Servo.h>


// create objects
Joystick myjoy(0, 1, 2);  // xPin, yPin, zPin
Motor motorTR(22,23,13);  // IN1, IN2, PWM
Motor motorBR(24,25,12);
Motor motorTL(26,27,11);
Motor motorBL(28,29,10);  
Motor motorMR(30,31,9);
Motor motorClawMove(32,33,8); 
MicroSwitch microTR(34);
MicroSwitch microBR(35);
MicroSwitch microTL(37);
MicroSwitch microBL(36);
MicroSwitch microMR(38);
MicroSwitch microML(39);
Servo motorClawOpen;  // the Pin is set in "setup"
int bigButton = 40;  // the Pin of bigButton

// Multiplying factors of turning speed
float BL = 1;
float BR = 0.8;
float TL = 1;
float TR = 1;
float ML = 1;

int y_speed = 0;
int x_speed = 0;


// different states
enum State {
  Idle = 0,
  Move = 1,
  Claw = 2,
  Return = 3,
};


State state = Move;

// buffer to print
char buf[100];


void setup() {
  // set the serial
  Serial.begin(9600); 
  motorClawOpen.attach(0);

  // TODO
  // set up the pin mode

}

void loop() {

    switch (state) {
      case Idle:
        sprintf(buf, "Idle");
        Serial.println(buf);

        // stop the motor  
          motorBL.motor_write(0);
          motorBR.motor_write(0);
          motorTL.motor_write(0);
          motorTR.motor_write(0);
          motorMR.motor_write(0);

        // do something

        // change the state to "Move"
        // Ask FANGMAMA
        // TODO

        break;

      case Move:
        // move the claw with input from joystick
    
        sprintf(buf, "Move");
        //sprintf(buf, "VRx=%d, VRy=%d", myjoy.calculate_motor_x(), myjoy.calculate_motor_y());
        sprintf(buf, "VRx=%d, VRy=%d", microMR.get_state(), microBR.get_state());
        Serial.println(buf);

        x_speed = myjoy.calculate_motor_x();
        y_speed = myjoy.calculate_motor_y();

        // y-axis (vertical)
        if(y_speed > 20 && !(microTL.get_state() || microTR.get_state())) {
          motorBL.motor_write(-floor(BL * y_speed));
          motorTL.motor_write(-floor(TL * y_speed));
          motorBR.motor_write(floor(BR * y_speed));
          motorTR.motor_write(floor(TR * y_speed));
        }
        else if (y_speed < -20 && !(microBL.get_state() || microBR.get_state())) {
          motorBL.motor_write(-floor(BL * y_speed));
          motorTL.motor_write(-floor(TL * y_speed));
          motorBR.motor_write(floor(BR * y_speed));
          motorTR.motor_write(floor(TR * y_speed));
        }
        else {
          motorBL.motor_write(0);
          motorBR.motor_write(0);
          motorTL.motor_write(0);
          motorTR.motor_write(0);
        }
        
        

        // x-axis (horizontal)
        if(x_speed > 20 && !microMR.get_state()) {
          motorMR.motor_write(-floor(ML * x_speed));
          motorClawMove.motor_write(-floor(ML * x_speed));
        }
        else if (x_speed < -20 && !microML.get_state()) {
          motorMR.motor_write(-floor(ML * x_speed));
          motorClawMove.motor_write(-floor(ML * x_speed));
        }
        else {
          motorMR.motor_write(0);
          motorClawMove.motor_write(0);
        }
 

      

        // if the big button is pressed
        if(!digitalRead(bigButton)) {
          // stop the motor  
          motorBL.motor_write(0);
          motorBR.motor_write(0);
          motorTL.motor_write(0);
          motorTR.motor_write(0);
          motorMR.motor_write(0);
          // change the state to "Claw"
          state = Claw;
        }

        break;

      case Claw:
        sprintf(buf, "Claw");
        Serial.println(buf);


        // claw move down
        motorClawMove.motor_write(200);
        delay(3000);
        motorClawMove.motor_write(0);

        delay(500);

        // close the claw
        motorClawOpen.write(180);

        delay(500);

        // claw move up
        motorClawMove.motor_write(-200);
        delay(3000);
        motorClawMove.motor_write(0);

        // change the state to "Return"
        state = Return;

        break;

      case Return:

        sprintf(buf, "Return");
        Serial.println(buf);
        delay(1000);

        // move to x = 0

        if(!microML.get_state()) {
          x_speed = -200;
          sprintf(buf, "Return to x = 0");
          Serial.println(buf);
          motorMR.motor_write(-floor(ML * x_speed));
        }
        else{
          motorMR.motor_write(0);
        }

        // move to y = 0
        if(!(microBL.get_state() || microBR.get_state())) {
          y_speed = -200;
          motorBL.motor_write(-floor(BL * y_speed));
          motorTL.motor_write(-floor(TL * y_speed));
          motorBR.motor_write(floor(BR * y_speed));
          motorTR.motor_write(floor(TR * y_speed));

          sprintf(buf, "Return to y = 0");
          Serial.println(buf);
        }
        else {
          motorBL.motor_write(0);
          motorBR.motor_write(0);
          motorTL.motor_write(0);
          motorTR.motor_write(0);
        }

        

        // If the claw is return to the start position
        if(microML.get_state() && (microBL.get_state() || microBR.get_state())) {

          delay(500);

          // open the claw
          motorClawOpen.write(0);

          delay(500);

          // change the state to "Idle"
          state = Idle;
        }
        
        break;

      default:
        // default behavior
        break;
  }
  
}
