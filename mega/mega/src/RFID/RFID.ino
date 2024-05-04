#include "RFID.h"

#define RST_PIN 49
#define SS_PIN 53

RFID *rfid;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid = new RFID(RST_PIN, SS_PIN);
}

void loop() {
  String str = rfid -> readID();
  if (str != "") {
    Serial.println(str);
  }
}
