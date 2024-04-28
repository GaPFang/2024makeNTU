#include <SoftwareSerial.h>

char val;

void setup() {
    Serial.begin(9600);
    Serial.println("BT is ready!");
    Serial1.begin(38400);
}

void loop() {
    if (Serial.available()) {
        val = Serial.read();
        Serial1.print(val);
    }

    if (Serial1.available()) {
        val = Serial1.read();
        Serial.print(val);
    }
}
