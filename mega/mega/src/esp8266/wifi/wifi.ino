void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);
}

void loop() {
    if (Serial1.available()) {
        Serial.println(Serial1.readString());
    }
    if (Serial.available()) {
        Serial1.println(Serial.readString());
    }
    Serial1.println("Hello from ESP8266!");
    delay(1000);
}
