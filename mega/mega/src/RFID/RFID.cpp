#include "RFID.h"

RFID::RFID() {
  this -> PCD_Init();
  SPI.begin();
  Serial.println("Read UID on a MIFARE PICC:");
}

RFID::RFID(byte rstPin, byte ssPin): MFRC522(ssPin, rstPin) {
  this -> PCD_Init();
  SPI.begin();
}

String RFID::readID() {
  Serial.println("Waiting for RFID..");
  int idSize = 0;
  byte *id;
  while (true) {
    if (!this -> PICC_IsNewCardPresent()) {
      continue;
    }
    if (!this -> PICC_ReadCardSerial()) {
      continue;
    }
    idSize = this -> uid.size;
    id = this -> uid.uidByte;
    break;
  }
  String idStr = "";
  for (byte i = 0; i < idSize; i++) {
    idStr += String(id[i], HEX);
  }
  digitalWrite(this -> rstPin, LOW);
  return idStr;
}

void RFID::flushRFID() {
}
