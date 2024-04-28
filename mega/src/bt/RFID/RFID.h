#include <SPI.h>
#include <MFRC522.h>

class RFID: public MFRC522{
  public:
    RFID();
    RFID(byte rstPin, byte ssPin): MFRC522(rstPin, ssPin){};
    void readData();
};