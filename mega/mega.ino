#include <Arduino.h>
#include "src/bt/BT.h"

BT *bt;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    bt = new BT();
}

void loop() {
    String str = bt -> btReadString();
    if (str != "") {
        Serial.println(str);
    }
    bt -> btSendString("Hello from mega!");
    delay(1000);
}