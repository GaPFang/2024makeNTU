#include <SoftwareSerial.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Serial started");
  Serial1.begin(9600);
  Serial.println("Serial1 started");
}

void loop() {
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}
