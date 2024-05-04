#include "myWifiClient.h"

MyWifiClient::MyWifiClient(){
    WiFi.mode(WIFI_STA);
}

void MyWifiClient::initWiFi(String hostName) {
    WiFi.disconnect();
    WiFi.begin(hostName, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println();
    Serial.print("Server IP: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Connected to ");
    Serial.println(hostName);
    while (!this -> client.connect(serverIP.c_str(), serverPort)) {
        Serial.println("Connection failed");
        delay(1000);
    }
    Serial.print("Connected to server ");
    Serial.println(serverIP);
}

String MyWifiClient::myWiFiReadString() {
    Serial.print("Waiting for response from server..");
    while (!this -> client.available()) {
        Serial.print('.');
        delay(100);
    }
    Serial.println();
    String line = this -> client.readStringUntil('\n');
    return line;
}

bool MyWifiClient::connectWithRFID(String rfid) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (rfid[j] != this -> rfid[i][j]) {
                break;
            }
            if (j == 6) {
                Serial.println("RFID found");
                this -> initWiFi(this -> host[i]);
                return true;
            }
        }
    }
    Serial.println("RFID not found");
    return false;
}

void MyWifiClient::sendToServer(String msg) {
    if (!this -> client) {
        return;
    }
    this -> client.println(msg);
}

String MyWifiClient::recieveFromServer() {
    while (!this -> client.available()) {
        delay(100);
    }
    String line = this -> client.readStringUntil('\n');
    return line;
}