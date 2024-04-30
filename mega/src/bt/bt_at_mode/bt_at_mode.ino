#include <SoftwareSerial.h>

#define VCC_PIN 42
#define EN_PIN 43

void setup() {
    Serial.begin(9600);
    Serial.println("BT is ready!");
    Serial1.begin(38400);
    pinMode(VCC_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(VCC_PIN, HIGH);
    digitalWrite(EN_PIN, HIGH);
}

void loop() {
    if (Serial.available()) {
        Serial1.println(Serial.readString());
    }

    if (Serial1.available()) {
        Serial.println(Serial1.readString());
    }
    Serial1.println("AT");
    delay(1000);
}
