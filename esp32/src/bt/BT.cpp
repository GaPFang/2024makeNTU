#include "BT.h"

BT::BT() {
    this->setPin("1234");
    this -> begin("ESP32test");
    Serial.println("BT object created");
}

String BT::ascii_to_string(char *data, int len) {
    String str = "";
    for (int i = 0; i < len; i++) {
        str += data[i];
    }
    return str;
}

String BT::btReadString() {
    String str = this -> readString();
    return str;
}

void BT::btSendString(String str) {
    this -> println(str);
}

void BT::printDeviceAddress() {
    const uint8_t* point = esp_bt_dev_get_address();
    for (int i = 0; i < 6; i++) {
        char str[3];
        sprintf(str, "%02X", (int)point[i]);
        Serial.print(str);

        if (i < 5) {
            Serial.print(":");
        }
    }
}