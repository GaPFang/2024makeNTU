#include "RFID.h"

RFID::RFID() {
  this -> PCD_Init();
  Serial.println(F("Read UID on a MIFARE PICC:"));
}

void RFID::readData() {
  if(!this -> PICC_IsNewCardPresent() || !this -> PICC_ReadCardSerial()) {
    return;
  }
  Serial.println(F("**Card Detected:**"));
  this -> PICC_DumpDetailsToSerial(&(this -> uid)); //讀出 UID
  this -> PICC_HaltA(); // 讓同一張卡片進入停止模式 (只顯示一次)
  this -> PCD_StopCrypto1(); // 停止 Crypto1
}