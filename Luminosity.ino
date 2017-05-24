#include "GroveColorSensor.h"

#define GAIN 64
#define UW_CM2_PER_COUNT_X64 77
#define LUX_PER_UW_CM2 6.83

#define Xe 0.3320
#define Ye 0.1858

void beginLuminosity() {
  Wire.begin();
  GroveColorSensor colorSensor;
}

int getColorTemperature() {
  GroveColorSensor colorSensor;
  double x, y;
  colorSensor.calculateCoordinate(&x, &y);
  return calculateTemperature(x, y);
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

static float calculateTemperature(float x, float y) {
  float n = (x - Xe)/(y - Ye);
  return -449*n*n*n + 3525*n*n - 6823.3*n + 5520.33;
}

