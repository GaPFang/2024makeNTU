#ifndef BT_H
#define BT_H

#include <SoftwareSerial.h>

// extern const String pswdTable[4][2];
// extern const int pswdTableSize;
class BT {
    public:
        BT();
        BT(int enPin, int ledPin);
        String dict(String id);
        void setPSWD(String id);
        String ascii_to_string(char *data, int len);
        String btReadString();
        void btSendString(String str);
    private:
        int enPin;
        int ledPin;
        String curID;
        const String pswdTable[4][2] = {
            {"13329ad", "0001"},
            {"6911b40", "0002"},
            {"56420d9", "0003"},
            {"82f5f85", "0004"}
        };
        const int pswdTableSize = 4;
};

#endif
