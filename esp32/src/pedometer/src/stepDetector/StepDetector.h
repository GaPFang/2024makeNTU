#ifndef STEP_DETECTOR_H
#define STEP_DETECTOR_H

class StepDetector {
public:
  StepDetector(float threshold, unsigned long debounceDelay, int bufferLength);
  void update(float x, float y, float z);
  int getStepCount() const;

private:
  float calculateMagnitude(float x, float y, float z);
  void detectStep(float magnitude);

  float threshold;
  unsigned long debounceDelay;
  unsigned long lastStepTime;
  bool stepDetected;
  int stepCount;
  int bufferLength;
  float *buffer;
  int bufferIndex;
};

#endif
