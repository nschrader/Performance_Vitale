#include <Wire.h>

#define UPDATE_INTERVAL 1000

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
  if (!validateMeasures(ppm, h, t, b, c, gps))
    return;
  String out = String(ppm) + ',' + String(h) + ',' + String(t) + ',' + String(b) + ',' + String(c) + ',' + gps + '\n';
  Serial.print(out);
  delay(UPDATE_INTERVAL);
}

bool validateMeasures(int ppm, float h, float t, int b, int c, char * gps) {
  return isValidTempHumidity(h, t) && isValidLuminosity(b, c) && isValidGPS(gps); // && ppm != -1;
}

