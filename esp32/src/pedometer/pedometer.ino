#include "src/oled/oled.h"
#include "src/adxl/adxl.h"
#include "src/stepDetector/StepDetector.h"
#include "src/constant.h"

OLED display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET);
ADXL accelerometer;
StepDetector stepDetector(THRESHOLD, DEBOUNCE_DELAY, BUFFER_LENGTH);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  display.init();
  accelerometer.init();
  stepDetector.loadStepCount();
}

void loop() {
  float x, y, z;
  if (accelerometer.readAcceleration(x, y, z)) {
    stepDetector.update(x, y, z);
    display.updateOledDisplay("Step Count: ", 2, stepDetector.getStepCount());
  }
}

void cleanup() {
  stepDetector.saveStepCount();
}
