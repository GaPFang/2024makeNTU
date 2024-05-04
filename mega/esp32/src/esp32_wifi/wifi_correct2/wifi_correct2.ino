// esp32
#include <WiFi.h>

String host[2] = {"esp32_1", "esp32_2"};
String password = "12345678";
String serverIP = "192.168.4.1";
int serverPort = 80;
WiFiClient *client; 
bool isConnected = false;

void initWiFi(int hostIdx) {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(host[hostIdx], password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println();
    Serial.print("Server IP: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Connected to ");
    Serial.println(host[hostIdx]);
    isConnected = false;
    while (!isConnected) {
        isConnected = client->connect(serverIP.c_str(), serverPort);
        Serial.println("Connection failed");
        delay(1000);
    }
    Serial.print("Connected to server ");
    Serial.println(serverIP);
}

void setup() {
    Serial.begin(9600);
    delay(100);
    client = new WiFiClient();
}

void loop() {
    for (int i = 0; i < 2; i++) {
        initWiFi(i);
        for (int j = 0; j < 3; j++) {
            client->println("Hello from ESP32");
            if (client->available()) {
                String line = client->readStringUntil('\n');
                Serial.println(line);
            }
            delay(1000);
        }
    }
}