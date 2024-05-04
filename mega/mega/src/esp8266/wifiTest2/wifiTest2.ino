#include <WiFi.h>

// Hardcode WiFi parameters as this isn't going to be moving around.
const char* ssid = "TCP_Server";
const char* password = "12345678";

// Start a TCP Server on port 5045
WiFiServer server(8080);
WiFiClient client = server.available();

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
 
  // Start the TCP server
  server.begin();
}

void loop() {
  TCPServer();
}

void TCPServer () {
    client = server.available();
    if (client){
        Serial.println("Client connected");
        String request = client.readStringUntil('\n');
        Serial.println(request);
        client.println("HTTP/1.1 200 OK");
        client.flush();
    }
}   
