#include <Arduino.h>
#include "BT.h"

BT::BT() {}

BT::BT(int enPin, int ledPin) {
    this -> enPin = enPin;
    this -> ledPin = ledPin;
    pinMode(enPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(enPin, LOW);
    digitalWrite(ledPin, LOW);
    Serial1.begin(9600);
    Serial.println("BT is ready!");
}

String BT::dict(String id) {
    for (int i = 0; i < pswdTableSize; i++) {
        if (id == pswdTable[i][0]) {
            return pswdTable[i][1];
        }
    }
}

void BT::setPSWD(String id) {
    if (id == this -> curID) {
        return;
    }
    digitalWrite(this -> ledPin, HIGH);
    this -> curID = id;
    String pswd = dict(id);
    Serial.println("Setting password to " + pswd);
    Serial1.begin(38400);
    digitalWrite(this -> enPin, HIGH);
    Serial1.println("AT+PSWD=" + pswd);
    Serial.println(Serial1.readString());
    delay(1000);
    Serial1.println("AT+PSWD?");
    Serial.println(Serial1.readString());
    delay(100);
    Serial1.println("AT+INIT");
    Serial.println(Serial1.readString());
    delay(100);
    digitalWrite(this -> enPin, LOW);
    Serial1.begin(9600);
    digitalWrite(this -> ledPin, LOW);
}

String BT::ascii_to_string(char *data, int len) {
    String str = "";
    for (int i = 0; i < len; i++) {
        str += data[i];
    }
    return str;
}

String BT::btReadString() {
    String str = "";
    if (Serial1.available()) {
        str = Serial1.readString();
    }
    return str;
}

void BT::btSendString(String str) {
    Serial1.println(str);
}
