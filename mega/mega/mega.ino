#include <Arduino.h>
#include <Servo.h>

#include "src/game/joystick.h"
#include "src/game/microswitch.h"
#include "src/game/motor.h"
#include "src/RFID/RFID.h"

RFID *rfid;
Joystick myjoy(0, 1, 2);  // xPin, yPin, zPin
Motor motorTR(22,23,13);  // IN1, IN2, PWMmotorClawOpen.write(180);
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
float MR = 1;

int y_speed = 0;
int x_speed = 0;

char buf[100];

#define RED_LED_PIN 47
#define GREEN_LED_PIN 48
#define RFID_RST_PIN 49
#define RFID_SS_PIN 53

void play() {
  // init the pin of motorClawOpen 
  motorClawOpen.attach(7);
  motorClawOpen.write(0);
  // set the state to "Move"
  Serial.println("Start");

  while (digitalRead(bigButton)) {
    sprintf(buf, "VRx=%d, VRy=%d", microMR.get_state(), microBR.get_state());
    Serial.println(buf);
    x_speed = -myjoy.calculate_motor_x();
    y_speed = -myjoy.calculate_motor_y();

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
      motorMR.motor_write(-floor(MR * x_speed));
    }
    else if (x_speed < -20 && !microML.get_state()) {
      motorMR.motor_write(-floor(MR * x_speed));
    }
    else {
      motorMR.motor_write(0);
    }
  }
  
  Serial.println("Claw");
  // claw move down
  motorClawOpen.write(0);
  delay(500);
  motorClawMove.motor_write(200);
  delay(700);
  motorClawMove.motor_write(0);
  delay(500);

  // close the claw
  motorClawOpen.write(180);
  delay(500);

  // claw move up
  motorClawMove.motor_write(-200);
  delay(1500);
  motorClawMove.motor_write(0);

  Serial.println("Return");
  delay(500);
  while(true) {

    // move to x = 0
  if(!microML.get_state()) {
    x_speed = -200;
    sprintf(buf, "Return to x = 0");
    Serial.println(buf);
    motorMR.motor_write(-floor(MR * x_speed));
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
  if(microMR.get_state() && (microBL.get_state() || microBR.get_state())) {
    delay(500);
    // open the claw
    motorClawOpen.write(0);
    delay(500);
    break;
  }
    }
  
  
  Serial.println("End");
  motorBL.motor_write(0);
  motorBR.motor_write(0);
  motorTL.motor_write(0);
  motorTR.motor_write(0);
  motorMR.motor_write(0);
}

void setup() {
    Serial.begin(9600);
    Serial2.begin(9600);
    SPI.begin();
    pinMode(RED_LED_PIN, OUTPUT);
    rfid = new RFID(RFID_RST_PIN, RFID_SS_PIN);
}

void loop() {
    String id = rfid -> readID();
    if (id != "") {
        digitalWrite(RED_LED_PIN, HIGH);
        Serial.println(id);
        Serial2.println(id);
        Serial.println("Waiting for ESP32..");
        while (!Serial2.available()) {
            delay(100);
        }
        String ret = Serial2.readString();
        Serial.println(ret);
        digitalWrite(RED_LED_PIN, LOW);
        if (ret[0] == 'S') {
            digitalWrite(GREEN_LED_PIN, HIGH);
            play();
            digitalWrite(GREEN_LED_PIN, LOW);
        }
   }
   delay(10);
}
