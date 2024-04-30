#include <SoftwareSerial.h>
#include "BT.h"

#define VCC_PIN 42
#define EN_PIN 43

BT *bt;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    bt = new BT(VCC_PIN, EN_PIN);
} 

void loop() {
    bt -> setPSWD("4321");
    if (Serial.available()) {
        Serial1.println(Serial.readString());
    }

    if (Serial1.available()) {
        Serial.println(Serial1.readString());
    }
    delay(100000);
}
