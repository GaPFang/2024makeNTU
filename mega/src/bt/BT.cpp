#include <Arduino.h>
#include "BT.h"

BT::BT() {
    Serial.println("BT is ready!");
}

String BT::ascii_to_string(char *data, int len) {
    String str = "";
    for (int i = 0; i < len; i++) {
        str += data[i];
    }
    return str;
}

String BT::btReadString() {
    String str = Serial1.readString();
    return str;
}

void BT::btSendString(String str) {
    Serial1.println(str);
}