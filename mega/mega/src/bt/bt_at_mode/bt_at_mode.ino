#include <SoftwareSerial.h>

#define EN_PIN 43

void setup() {
    Serial.begin(9600);
    Serial.println("BT is ready!");
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH);
    Serial1.begin(38400);
}

void loop() {
    if (Serial.available()) {
        Serial1.println(Serial.readString());
    }

    if (Serial1.available()) {
        Serial.println(Serial1.readString());
    }
}
