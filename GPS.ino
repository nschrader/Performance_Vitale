#include <SoftwareSerial.h>

#define GPS_RX 12
#define GPS_TX 11

SoftwareSerial SoftSerial(GPS_RX, GPS_TX);
char buffer[64];
int count = 0;

void beginGPS() {
  SoftSerial.begin(9600);
}

void readGPS() {
  while (SoftSerial.available())
  {
    buffer[count++] = SoftSerial.read();  
    if (count == 64)
      break;
    if (!strcmp(&buffer[count-2], "$$"))
      break;
  }
  //if (!strcmp(buffer, "$GPGGA"))
    Serial.write(buffer, count);
    Serial.write('\n');
  count = 0;
}


void clearBufferArray()
{
  for (int i = 0; i < count; i++)
    buffer[i] = NULL;
}
