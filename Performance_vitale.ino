#define UPDATE_INTERVAL 1000

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(getCO2());
  Serial.print('\n');
  delay(UPDATE_INTERVAL);
}
