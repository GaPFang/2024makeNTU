#include <Arduino.h>
#include "BT.h"

BT::BT(int vccPin, int enPin) {
    this->vccPin = vccPin;
    this->enPin = enPin;
    pinMode(vccPin, OUTPUT);
    pinMode(enPin, OUTPUT);
    digitalWrite(vccPin, HIGH);
    digitalWrite(enPin, LOW);
    Serial.println("BT is ready!");
}

void BT::setPSWD(String pswd) {
    Serial1.begin(38400);
    digitalWrite(this -> enPin, HIGH);
    Serial1.println("AT+PSWD=" + pswd);
    delay(1000);
    Serial1.println("AT+PSWD?");
    delay(100);
    Serial1.println("AT+INIT");
    delay(100);
    digitalWrite(this -> enPin, LOW);
    Serial1.begin(9600);
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
