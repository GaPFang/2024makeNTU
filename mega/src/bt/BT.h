#include <SoftwareSerial.h>

class BT {
    public:
        BT(int vccPin, int enPin);
        void setPSWD(String pswd);
        String ascii_to_string(char *data, int len);
        String btReadString();
        void btSendString(String str);
    private:
        int vccPin;
        int enPin;
};
