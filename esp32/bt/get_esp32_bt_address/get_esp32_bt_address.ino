/*
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:1
load:0x3fff0030,len:1344
load:0x40078000,len:13964
load:0x40080400,len:3600
entry 0x400805f0
Failed to enable bluedroid
C8:F0:9E:EA:BB:8E
C8F0,9E,EABB8E
*/

#include "esp_bt_device.h"
#include "esp_bt_main.h"

bool initBluetooth() {
    if (!btStart()) {
        Serial.println("Failed to initialize controller");
        return false;
    }

    if (esp_bluedroid_init() != ESP_OK) {
        Serial.println("Failed to initialize bluedroid");
        return false;
    }

    if (esp_bluedroid_enable() != ESP_OK) {
        Serial.println("Failed to enable bluedroid");
        return false;
    }
}

void printDeviceAddress() {
    const uint8_t* point = esp_bt_dev_get_address();
    // This function takes no arguments and
    // returns the six bytes of the Bluetooth device address.
    // Note that the six bytes will be returned as a pointer to an array of uint8_t, 
    // which we will store on a variable.
    for (int i = 0; i < 6; i++) {
        char str[3];

        sprintf(str, "%02X", (int)point[i]);
        Serial.print(str);

        if (i < 5) {
            Serial.print(":");
        }
    }
}

void setup() {
    Serial.begin(115200);

    initBluetooth();
    printDeviceAddress();
}

void loop() {}  
