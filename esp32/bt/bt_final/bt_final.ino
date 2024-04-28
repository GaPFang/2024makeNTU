#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
char *pin = "1234";  //建立連接時的密碼，不設置與hc05連接不上

// ascii to string
String ascii_to_string(char *data, int len) {
    String str = "";
    for (int i = 0; i < len; i++) {
        str += data[i];
    }
    return str;
}

void setup() {
    Serial.begin(9600);
    SerialBT.setPin(pin);
    SerialBT.begin("ESP32test");  //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
    if (SerialBT.available()) {
        Serial.println(SerialBT.readString());
    }
}
