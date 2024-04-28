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
}

void loop() {
  float accelerationX, accelerationY, accelerationZ;
  if (accelerometer.readAcceleration(accelerationX, accelerationY, accelerationZ)) {
    stepDetector.update(accelerationX, accelerationY, accelerationZ);
    display.updateOledDisplay("Step Count: ", 2, stepDetector.getStepCount());
  }
}
