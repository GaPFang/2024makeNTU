#include "src/bt/BT.h"

BT *bt;

void setup() {
    Serial.begin(9600);
    bt = new BT();
}

void loop() {
    String str = bt -> btReadString();
    if (str != "") {
        Serial.println(str);
    }
    bt -> btSendString("Hello from ESP32");
    delay(1000);
}