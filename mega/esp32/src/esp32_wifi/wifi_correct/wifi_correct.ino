// esp32
#include <WiFi.h>

String host = "esp32_1";
String password = "12345678";
String serverIP = "192.168.4.1";
int serverPort = 80;
WiFiClient *client; 
bool isConnected = false;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(host, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
  delay(100);
  client = new WiFiClient();
}

void loop() {
  delay(1000);
  if (!isConnected) {
    isConnected = client->connect(serverIP.c_str(), serverPort);
    Serial.println("Connection failed");
    return;
  }
  Serial.println("Connected to server");
  client->println("43");
  // if (client->available()) {
  //   String line = client->readStringUntil('\n');
  //   Serial.println(line);
  // }
}
