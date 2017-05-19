#include "GroveColorSensor.h"

GroveColorSensor colorSensor;

void beginLuminosity() {
  colorSensor.ledStatus = 0;
}

void getColorTemperature() {
  int red, green, blue, clear;
  colorSensor.readRGBC(&red, &green, &blue, &clear);
  Serial.print(clear);
}

void getBrightness() {
  
}

