#include "wifi.h"

WiFiManager::WiFiManager(String ssid, String password, int port): ssid(ssid), password(password) {
  this->server = WiFiServer(port);
}

// WiFiManager::~WiFiManager() {
//   this->server.stop();
// }

void WiFiManager::setupWiFiAP() {
  Serial.print("Setting AP...");
  WiFi.softAP(this->ssid, this->password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(IP);
  // starting the server
  server.begin();
  Serial.println("Server started at port 80");
}

int WiFiManager::handleApClient() {
  // if (this -> client) {
  //   return;
  // }
  // Serial.print("Waiting for client connecting...");
  // while(!(this -> client = this->server.available())) {
    // Serial.print(".");
    // delay(100);
  // }
  if (this -> client) {
    this -> client.flush();
  }
  this -> client = this->server.available();
  // Serial.println();
  if (!this -> client) {
    return 0;
  }
  Serial.println("Client connected");
  Serial.print("Waiting for client sending..");
  while (!client.available()) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  String line = this ->client.readStringUntil('\n');
  int count = line.toInt();
  return count;
}

// int WiFiManager::getStepCount() {
//   if (!this -> client) {
//     return 0;
//   }
//   Serial.print("Waiting for client sending...");
//   while (!this -> client.available()) {
//     Serial.print(".");
//     delay(100);
//   }
//   Serial.println();
//   String line = this ->client.readStringUntil('\n');
//   int count = line.toInt();
//   if (count == 0) {
//     Serial.println("Client exited");
//     this ->client.flush();
//   }
//   return count;
// }

void WiFiManager::sendStatus(String status) {
  if (!this -> client) {
    return;
  }
  this -> client.println(status);
}