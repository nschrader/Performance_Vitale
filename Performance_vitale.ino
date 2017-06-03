#include <Wire.h>

#define UPDATE_INTERVAL 1000
//#define DEBUG

bool heating = true;

void setup() {
  Serial.begin(9600);
  beginDHT();
  beginGPS();
  beginLuminosity();
}

void loop() {
  int ppm = getCO2();
  float h = getHumidity();
  float t = getTemperature();
  int b = getBrightness();
  int c = getColorTemperature();
  char* gps = readGPS();
  if(!isValidGPS(gps)){
    gps="0,N,0,E";
  }
  bool ok = validateMeasures(ppm, h, t, b, c, gps);
#ifndef DEBUG
  if (!ok && heating) {
    Serial.print("Heating\n");
  } else if (ok) {
    heating = false;
#endif
    String out = String(ppm) + ',' + String(h) + ',' + String(t) + ',' + String(b) + ',' + String(c) + ',' + gps + '\n';
    Serial.print(out);
#ifndef DEBUG
  }
#endif
  delay(UPDATE_INTERVAL);
}

bool validateMeasures(int ppm, float h, float t, int b, int c, char * gps) {
  return isValidTempHumidity(h, t) && isValidLuminosity(b, c); // && ppm != -1;
}
