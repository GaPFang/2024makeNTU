#include <WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial1.println("AT");
  delay(100);
  Serial1.println("AT+CWMODE=1");
  delay(100);
  Serial1.println("AT+CIPMUX=0");
  delay(100);
//  TCP_Server, 12345678
  Serial1.println("AT+CWJAP_DEF=\"esp32_1\",\"12345678\"");
  delay(100);
  Serial1.println("AT+CIPSTART=\"esp32_1\", \"192.168.4.1\", 80");
//  WiFi.begin("esp32_1", "12345678");
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.println(WiFi.status());
//  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available()) {
    Serial.println(Serial1.readString());
  }
  if (Serial.available()) {
    Serial1.println(Serial.readString());
  }
  delay(100);
}
