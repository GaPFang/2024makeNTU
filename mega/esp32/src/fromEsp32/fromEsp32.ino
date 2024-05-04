//#include <HardwareSerial.h>
//
//HardwareSerial SerialPort(2);

void setup() {
    Serial.begin(9600);
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
    Serial2.setTimeout(10);
}

void loop() {
    if (Serial2.available()) {
        String ret = Serial2.readString();
        Serial.println(ret);
    }
    Serial2.println("Hello from esp32 using Rx Tx!");
    delay(1000);
}
