#include <SoftwareSerial.h>

#define GPS_RX 12
#define GPS_TX 11

SoftwareSerial SoftSerial(GPS_RX, GPS_TX);
char buffer[64];
int count = 0;

void beginGPS() {
  SoftSerial.begin(9600);
}

char *readGPS() {
  clearBufferArray();
  while (SoftSerial.available())
  {
    buffer[count++] = SoftSerial.read();  
    if (count == 64)
      break;
    if (!strcmp(&buffer[count-2], "$$"))
      break;
  }
  count = 0;
  if (!strncmp(buffer, "$GPGGA", 5))
    return buffer;
   else
    return NULL;
}


void clearBufferArray() {
  for (int i = 0; i < count; i++)
    buffer[i] = NULL;
}
