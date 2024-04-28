#include <BluetoothSerial.h>

#include "esp_bt_device.h"
#include "esp_bt_main.h"

class BT: public BluetoothSerial {
    public:
        BT();
        String ascii_to_string(char *data, int len);
        String btReadString();
        void btSendString(String str);
        void printDeviceAddress();
};