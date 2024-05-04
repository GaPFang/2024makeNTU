void setup() {
    Serial.begin(115200);
    Serial2.begin(9600);
    pinMode(43, OUTPUT);
    Serial2.setTimeout(10);
}

void loop() {
    if (Serial2.available()) {
        digitalWrite(43, HIGH);
        String ret = Serial2.readString();
        digitalWrite(43, LOW);
        Serial.println(ret);
    }
    Serial2.println("Hello from Mega using Rx Tx!");
    delay(1000);
}
