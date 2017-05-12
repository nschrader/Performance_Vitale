#define UPDATE_INTERVAL 1000

void setup() {
  Serial.begin(9600);
  beginDHT();
  beginGPS();
}

void loop() {
  //int ppm = getCO2();
  //float h = getHumidity();
  //float t = getTemperature();
  //String out = String(ppm) + ", " + String(h) + ", " + String(t) + '\n';
  //Serial.print(out);
  readGPS();
  delay(UPDATE_INTERVAL);
}
