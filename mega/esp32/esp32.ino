#include "src/esp32_wifi/myWifiClient.h"

MyWifiClient *wifiClient;

void setup() {
    Serial.begin(9600);
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
    Serial2.setTimeout(10);
    wifiClient = new MyWifiClient();
}

void loop() {
    delay(100);
    Serial.println("Waiting for Mega..");
    while (!Serial2.available()) {
        delay(100);
    }
    String rfid = Serial2.readString();
    Serial.println(rfid);
    bool rfidExist = wifiClient -> connectWithRFID(rfid);
    if (!rfidExist) {
        return;
    }
    wifiClient -> sendToServer("43");
    String response = wifiClient -> recieveFromServer();
    Serial.println(response);
    Serial2.println(response);
}