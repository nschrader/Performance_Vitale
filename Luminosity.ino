#include "GroveColorSensor.h"

#define GAIN 64
#define UW_CM2_PER_COUNT_X64 77
#define LUX_PER_UW_CM2 7

void beginLuminosity() {
  Wire.begin();
  GroveColorSensor colorSensor;
}

int getColorTemperature() {
  GroveColorSensor colorSensor;
  double x, y;
  colorSensor.calculateCoordinate(&x, &y);
  return calculateXTemperature(x);
}

int getBrightness() {
  GroveColorSensor colorSensor;
  unsigned int _red, _green, _blue, _clear;
  colorSensor.readRGBC(&_red, &_green, &_blue, &_clear);
  float clear = _clear;
  clear /= GAIN;
  clear *= UW_CM2_PER_COUNT_X64 / 64;
  clear *= LUX_PER_UW_CM2;
  return clear;
}

bool isValidLuminosity(int b, int c) {
  return b > 0 && b < 7000 && c > 1000 && c < 10000;
}

static float calculateXTemperature(float x) {
  return 69129*x*x-90610*x+30594;
}

