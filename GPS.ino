#include <SoftwareSerial.h>

#define GPS_RX 12
#define GPS_TX 11

#define BUFFER_LENGTH 64
#define LAT_OFFSET 18
#define LAT_LONG_LENGTH 24

SoftwareSerial GPSSerial(GPS_RX, GPS_TX);
char buffer[BUFFER_LENGTH];
char out[LAT_LONG_LENGTH+1];
int count = 0;

void beginGPS() {
  GPSSerial.begin(9600);
}

char *readGPS() {
  clearBufferArray();
  while (GPSSerial.available())
  {
    buffer[count++] = GPSSerial.read();  
    if (count == BUFFER_LENGTH)
      break;
    if (!strcmp(&buffer[count-2], "$$"))
      break;
  }
  count = 0;
#ifdef DEBUG
  Serial.println(buffer);
#endif
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

bool isValidGPS(char *gps) {
  if (gps == NULL)
    return;
  bool n, s, w, e;
  n = strstr(gps, "N") != NULL;
  s = strstr(gps, "S") != NULL;
  w = strstr(gps, "W") != NULL;
  e = strstr(gps, "E") != NULL;
  return (n || s) && (w || e);
}

