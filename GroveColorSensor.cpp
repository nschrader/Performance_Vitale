#include "GroveColorSensor.h"
#include <Wire.h>
#include <math.h>

// Default constructor
GroveColorSensor::GroveColorSensor()
  : triggerMode_(INTEG_MODE_FREE | INTEG_PARAM_PULSE_COUNT1)
  , interruptSource_(INT_SOURCE_CLEAR)
  , interruptMode_(INTR_LEVEL | INTR_PERSIST_EVERY)
  , gainAndPrescaler_(GAIN_64 | PRESCALER_1)
  , sensorAddress_(COLOR_SENSOR_ADDR)
{
  GroveColorSensor::setTimingReg();
  GroveColorSensor::setInterruptSourceReg();
  GroveColorSensor::setInterruptControlReg();
  GroveColorSensor::setGain();
  GroveColorSensor::setEnableADC();
}

// Constructor with parameters
GroveColorSensor::GroveColorSensor(
  const int& triggerMode
  , const int& interruptSource
  , const int& interruptMode
  , const int& gainAndPrescaler
  , const int& sensorAddress)
  : triggerMode_(triggerMode)
  , interruptSource_(interruptSource)
  , interruptMode_(interruptMode)
  , gainAndPrescaler_(gainAndPrescaler)
  , sensorAddress_(sensorAddress)
{}

void GroveColorSensor::setTimingReg()
{
  Wire.beginTransmission(sensorAddress_);
  Wire.write(REG_TIMING);
  Wire.write(triggerMode_);
  Wire.endTransmission();
  delay(10);
}

void GroveColorSensor::setInterruptSourceReg()
{
  Wire.beginTransmission(sensorAddress_);
  Wire.write(REG_INT_SOURCE);
  Wire.write(interruptSource_);
  Wire.endTransmission();
  delay(10);
}

void GroveColorSensor::setInterruptControlReg()
{
  Wire.beginTransmission(sensorAddress_);
  Wire.write(REG_INT);
  Wire.write(interruptMode_);
  Wire.endTransmission();
  delay(10);
}

void GroveColorSensor::setGain()
{
  Wire.beginTransmission(sensorAddress_);
  Wire.write(REG_GAIN);
  Wire.write(gainAndPrescaler_);
  Wire.endTransmission();
}

void GroveColorSensor::setEnableADC()
{
  Wire.beginTransmission(sensorAddress_);
  Wire.write(REG_CTL);
  Wire.write(CTL_DAT_INIITIATE);
  Wire.endTransmission();
  delay(10);
}

void GroveColorSensor::clearInterrupt()
{
  Wire.beginTransmission(sensorAddress_);
  Wire.write(CLR_INT);
  Wire.endTransmission();
}

void GroveColorSensor::readRGBC(int *red, int *green, int *blue, int *clear)
{
  Wire.beginTransmission(sensorAddress_);
  Wire.write(REG_BLOCK_READ);
  Wire.endTransmission();

  Wire.requestFrom(sensorAddress_, 8);

  // if two bytes were received
  if (8 <= Wire.available())
  {
    int i;
    for (i = 0; i < 8; ++i)
    {
      readingdata_[i] = Wire.read();
      //Serial.println(readingdata_[i]);
    }
  }
  
  green_  = readingdata_[1] * 256 + readingdata_[0];
  red_  = readingdata_[3] * 256 + readingdata_[2];
  blue_ = readingdata_[5] * 256 + readingdata_[4];
  clear_  = readingdata_[7] * 256 + readingdata_[6];

  double tmp;
  int maxColor;

  maxColor = max(red_, green_);
  maxColor = max(maxColor, blue_);

  tmp = 250.0 / maxColor;
  *green = green_	* tmp;
  *red = red_ * tmp;
  *blue = blue_	* tmp;
  *clear = clear_;
}

void GroveColorSensor::calculateCoordinate(double *xValue, double *yValue)
{
  int red, green, blue, clear;
  readRGBC(&red, &green, &blue, &clear);
  
  double X;
  double Y;
  double Z;
  double x;
  double y;

  X = (-0.14282) * red + (1.54924) * green + (-0.95641) * blue;
  Y = (-0.32466) * red + (1.57837) * green + (-0.73191) * blue;
  Z = (-0.68202) * red + (0.77073) * green + (0.563320) * blue;

  x = X / (X + Y + Z);
  y = Y / (X + Y + Z);

  if ( (X > 0) && ( Y > 0) && ( Z > 0) )
  {
    *xValue = x;
    *yValue = y;
  }
  else {
    *xValue = -1;
    *yValue = -1;
  }
}
