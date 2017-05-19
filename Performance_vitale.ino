#include <Wire.h>

#define UPDATE_INTERVAL 1000

void setup() {
  Serial.begin(9600);
  beginDHT();
  beginGPS();
  Serial.print("Test1");
  beginLuminosity();
}

void loop() {
  //int ppm = getCO2();
  //float h = getHumidity();
 // float t = getTemperature();
  //char* gps = readGPS();
  //if (!validateMeasures(ppm, h, t, gps))
  //  return;
 // String out = String(ppm) + ',' + String(h) + ',' + String(t) + ',' + gps + '\n';
  //Serial.print(out);
  Serial.print("Test2");
  getColorTemperature();
  delay(UPDATE_INTERVAL);
}

bool validateMeasures(int ppm, float h, float t, char * gps) {
  return isValidTempHumidity(h, t) && isValidGPS(gps); // && ppm != -1;
}

