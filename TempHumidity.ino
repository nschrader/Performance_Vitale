#include "DHT.h"

#define DHTPIN 13     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

void beginDHT() {
  dht.begin();
}

float getHumidity() {
  return dht.readHumidity();
}

float getTemperature() {
  return dht.readTemperature();
}

bool isValidTempHumidity(float h, float t) {
  return h != 0.0 && t != 0.0;
}

