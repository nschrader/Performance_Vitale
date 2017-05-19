#include "GroveColorSensor.h"

void beginLuminosity() {
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

void getBrightness() {
  GroveColorSensor colorSensor;
  int red, green, blue, clear;
  colorSensor.readRGBC(&red, &green, &blue, &clear);
  Serial.print(clear);  
}

