#include "GroveColorSensor.h"

#define GAIN 64
#define UW_CM2_PER_COUNT_X64 77
#define LUX_PER_UW_CM2 7

void beginLuminosity() {
  Wire.begin();
  GroveColorSensor colorSensor;
  colorSensor.ledStatus = 0;
}

void getColorTemperature() {
  GroveColorSensor colorSensor;
  double x, y;
  colorSensor.calculateCoordinate(&x, &y);
  Serial.print(x); 
  Serial.print(y); 
}

float getBrightness() {
  GroveColorSensor colorSensor;
  int _red, _green, _blue, _clear;
  colorSensor.readRGBC(&_red, &_green, &_blue, &_clear);
  float clear = _clear;
  clear /= GAIN;
  clear *= UW_CM2_PER_COUNT_X64 / 64;
  clear *= LUX_PER_UW_CM2;
  return clear;
}

