#include "RFID.h"

RFID::RFID() {
  this -> PCD_Init();
  SPI.begin();
  Serial.println(F("Read UID on a MIFARE PICC:"));
}

RFID::RFID(byte rstPin, byte ssPin): MFRC522(rstPin, ssPin) {
  this -> PCD_Init(ssPin, rstPin);
  SPI.begin();
  Serial.println(F("Read UID on a MIFARE PICC:"));
}

String RFID::readData() {
  // if(!this -> PICC_IsNewCardPresent() || !this -> PICC_ReadCardSerial()) {
  //   return;
  // }
  // Serial.println(F("**Card Detected:**"));
  // this -> PICC_DumpDetailsToSerial(&(this -> uid)); //讀出 UID
  // this -> PICC_HaltA(); // 讓同一張卡片進入停止模式 (只顯示一次)
  // this -> PCD_StopCrypto1(); // 停止 Crypto1
  int idSize = 0;
  if (this -> PICC_IsNewCardPresent() && this -> PICC_ReadCardSerial()) {
    byte *id = this -> uid.uidByte;
    idSize = this -> uid.size;
    String idStr = "";
    for (byte i = 0; i < idSize; i++) {
      idStr += String(id[i], HEX);
    }
    return idStr;
  }
  return "";
}
