#include <WiFi.h>

const char* ssid = "TCP_Server";//type your ssid
const char* password = "12345678";//type your password
 
WiFiServer server(80);//Service Port
 
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
//  delay(10);
//  Serial.print("Server started: ");
//  Serial.println(WiFi.localIP());
}
 
void loop() {
//  // Check if a client has connected
//  WiFiClient client = server.available();
//  if (!client) {
//    return;
//  }
//   
//  // Wait until the client sends some data
//  Serial.println("new client");
//  while(!client.available()){
//    delay(1);
//  }
//   
//  // Read the first line of the request
//  String request = client.readStringUntil('\n');
//  Serial.println(request);
////  client.println("HTTP/1.1 200 OK");
//   client.println("Hello from Server");
//  client.flush();
// 
//  delay(1);
//  Serial.println("Client disconnected");
}
