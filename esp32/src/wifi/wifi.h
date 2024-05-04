#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

class WiFiManager {
  public:
    WiFiManager(String ssid, String password, int port);  // Constructor
    // ~WiFiManager(); // Destructor
    void setupWiFiAP();
    int handleApClient();
    // int getStepCount();
    void sendStatus(String status);
  private:
    String ssid;
    String password;
    WiFiServer server;
    WiFiClient client;
};

#endif