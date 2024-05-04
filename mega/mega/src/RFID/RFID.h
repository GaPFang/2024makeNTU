#ifndef RFID_H
#define RFID_H

#include <SPI.h>
#include <MFRC522.h>

class RFID: public MFRC522{
  public:
    RFID();
    RFID(byte rstPin, byte ssPin);
    String readID();
    void flushRFID();
  private:
    byte rstPin;
    byte ssPin;
};

#endif