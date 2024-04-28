#include <SoftwareSerial.h>

class BT {
    public:
        BT();
        String ascii_to_string(char *data, int len);
        String btReadString();
        void btSendString(String str);
};