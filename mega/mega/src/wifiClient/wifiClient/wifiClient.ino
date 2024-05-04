//mega
#include <WiFi.h>

WiFiClient *client;
const char *ssid[3] = {"esp32_1", "esp32_2", "esp32_3"};
const char *password = "12345678";
const char *serverIP = "192.168.4.1";
const int serverPort = 80;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid[0]);

  WiFi.begin(ssid[0], password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
    Serial.println(WiFi.status());
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client = new WiFiClient();
}

void loop() {
  if (!client->connect(serverIP, serverPort)) {
    Serial.println("Connection failed");
    return;
  }
  Serial.print("Connected to server ");
  Serial.println(ssid[0]);

  while (client->available()) {
    client->println("Hello from client!");
    String line = client->readStringUntil('\n');
    if (line != "") {
        Serial.println(line);
    }
    delay(1000);
  }

  Serial.println();
  Serial.println("closing connection");
  client->stop();

  delay(5000);
}
