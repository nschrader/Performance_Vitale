#include <SoftwareSerial.h>

#define GPS_RX 12
#define GPS_TX 11

#define BUFFER_LENGTH 64
#define LAT_OFFSET 18
#define LAT_LONG_LENGTH 24

SoftwareSerial SoftSerial(GPS_RX, GPS_TX);
char buffer[BUFFER_LENGTH];
char out[LAT_LONG_LENGTH+1];
int count = 0;

void beginGPS() {
  SoftSerial.begin(9600);
}

char *readGPS() {
  clearBufferArray();
  while (SoftSerial.available())
  {
    buffer[count++] = SoftSerial.read();  
    if (count == BUFFER_LENGTH)
      break;
    if (!strcmp(&buffer[count-2], "$$"))
      break;
  }
  count = 0;
  if (!strncmp(buffer, "$GPGGA", 5)) {
    parseGPGGA();
    return out;
  } else
    return NULL;
}

void clearBufferArray() {
  for (int i = 0; i < count; i++)
    buffer[i] = NULL;
}

void parseGPGGA() {
  strncpy(out, buffer + LAT_OFFSET, LAT_LONG_LENGTH);
}

