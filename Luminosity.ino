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
  Serial.println("X=" + String(x) + " Y=" + String(y));
  float t = calculateYTemperature(y);
  t += calculateYTemperature(y);
  Serial.println("T=" + String(t/2));
  return t/2;
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
  return b > 0 && b < 100.000 && c > 1000 && c < 10000;
}

static float calculateXTemperature(float x) {
  return 69129*x*x-90610*x+30594;
}

static float calculateYTemperature(float y) {
  double t = -1.54701*100*y*y*y + 1.6825*100*y*y - 6.03692*10*y + 7.14024; //00000
  return t * 100000;
}

