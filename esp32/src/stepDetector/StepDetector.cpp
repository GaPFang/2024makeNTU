#include "StepDetector.h"
#include "../constant.h"
#include <Arduino.h>
#include <math.h>

StepDetector::StepDetector(float threshold, unsigned long debounceDelay, int bufferLength, int eepromAddress)
    : threshold(threshold), debounceDelay(debounceDelay),
      bufferLength(bufferLength), eepromAddress(eepromAddress), stepCount(0),
      stepDetected(false), lastStepTime(0), bufferIndex(0) {
  this->buffer = new float[this->bufferLength]();
  EEPROM.begin(EEPROM_SIZE);
}

StepDetector::~StepDetector() {
  delete[] this->buffer;
}

void StepDetector::update(float x, float y, float z) {
  float magnitude = calculateMagnitude(x, y, z);
  this->buffer[this->bufferIndex] = magnitude;
  this->bufferIndex = (this->bufferIndex + 1) % this->bufferLength;
  detectStep(magnitude);
}

float StepDetector::calculateMagnitude(float x, float y, float z) {
  return sqrt(x * x + y * y + z * z);
}

void StepDetector::detectStep(float magnitude) {
  float avgMagnitude = 0;
  for (int i = 0; i < this->bufferLength; i++) {
    avgMagnitude += this->buffer[i];
  }
  avgMagnitude /= this->bufferLength;

  unsigned long currentMillis = millis();

  if (magnitude > (avgMagnitude + this->threshold)) {
    if (!this->stepDetected && (currentMillis - this->lastStepTime) > this->debounceDelay) {
      this->stepCount++;
      this->stepDetected = true;
      this->lastStepTime = currentMillis;
    }
  } else {
    this->stepDetected = false;
  }
}

int StepDetector::getStepCount() { 
  if (this->stepCount > 0) {
    return this->stepCount;
  }
  return this->stepCount;
}

void StepDetector::saveStepCount() {
  EEPROM.write(10, this->stepCount);
  EEPROM.commit();
}

void StepDetector::loadStepCount() {
  this->stepCount = EEPROM.readInt(10);
  if (this->stepCount < 0) {
    this->stepCount += 255;
  }
}

void StepDetector::resetStepCount() {
  this->stepCount = 0;
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
}

bool StepDetector::decrementStepCount(int count) {
  if (this->stepCount < count) {
    return false;
  }
  this->stepCount -= count;
  return true;
}