#include <SoftwareSerial.h>
#include "BT.h"

#define EN_PIN 42
#define LED_PIN 43

BT *bt;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    bt = new BT(EN_PIN, LED_PIN);
} 

void loop() {
    bt -> setPSWD("13329ad");
    if (Serial.available()) {
        Serial1.println(Serial.readString());
    }

    if (Serial1.available()) {
        Serial.println(Serial1.readString());
    }
    delay(100000);
}
