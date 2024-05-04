#include <Arduino.h>
//#include <pthread.h>

#include "src/RFID/RFID.h"

RFID *rfid;

#define LED_PIN 43
#define RFID_RST_PIN 49
#define RFID_SS_PIN 53

void setup() {
    Serial.begin(9600);
    Serial2.begin(9600);
    SPI.begin();
    pinMode(LED_PIN, OUTPUT);
    rfid = new RFID(RFID_RST_PIN, RFID_SS_PIN);
}

void loop() {
    String id = rfid -> readID();
    if (id != "") {
        digitalWrite(LED_PIN, HIGH);
        Serial.println(id);
        Serial2.println(id);
        Serial.println("Waiting for ESP32..");
        while (!Serial2.available()) {
            delay(100);
        }
        String ret = Serial2.readString();
        Serial.println(ret);
        digitalWrite(LED_PIN, LOW);
        rfid -> flushRFID();
   }
   delay(10);
}
