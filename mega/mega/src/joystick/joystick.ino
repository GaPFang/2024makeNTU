#include <stdio.h>
#include <Arduino.h>

#define PIN_ANALOG_X A14
#define PIN_ANALOG_Y A15

#define AIN1      A2 //定義 A1 接腳（右）
#define AIN2      A3 //定義 A2 接腳（右）
#define PWMA    A11//定義 ENA (PWM調速) 接腳
#define BIN1      A5 //定義 B1 接腳（左）
#define BIN2      A6 //定義 B2 接腳（左）
#define PWMB    A12//定義 ENB (PWM調速) 接腳

void setup() {
    Serial.begin(9600);
    pinMode(PIN_ANALOG_X, INPUT);
    pinMode(PIN_ANALOG_Y, INPUT);
    pinMode(AIN1, OUTPUT); //設定 A1 接腳為輸出
    pinMode(AIN2, OUTPUT); //設定 A2 接腳為輸出
    pinMode(PWMA, OUTPUT); //設定 ENA 接腳為輸出
    pinMode(BIN1, OUTPUT); //設定 B1 接腳為輸出
    pinMode(BIN2, OUTPUT); //設定 B2 接腳為輸出
    pinMode(PWMB, OUTPUT); //設定 ENB 接腳為輸出
}

int tmp_x, tmp_y;
int x, y;

void loop() {
    tmp_x = analogRead(PIN_ANALOG_X) - 270;
    tmp_y = analogRead(PIN_ANALOG_Y);
    if (tmp_x < 200 && tmp_x > -200) {
        x = 1;
    } else {
        x = tmp_x < 0 ? 0 : 2;
    }
    if (tmp_y < 200 && tmp_y > -200) {
        y = 1;
    } else {
        y = tmp_y < 0 ? 0 : 2;
    }
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 160);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, 160);
    if (x == 1) {
        analogWrite(PWMA, 0);
    } else if (x == 0) {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        analogWrite(PWMA, 160);
    } else {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        analogWrite(PWMA, 160);
    }
    if (y == 1) {
        analogWrite(PWMB, 0);
    } else if (y == 0) {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
        analogWrite(PWMB, 160);
    } else {
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
        analogWrite(PWMB, 160);
    }
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);
    delay(100);
}
