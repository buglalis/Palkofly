#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

float gps_data()
{
  
}

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
}

void loop()
{
  while (ss.available() > 0)
    gps.encode(ss.read());
  if (gps.altitude.isUpdated())
    Serial.println(gps.altitude.meters());
  
  Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
  Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
  Serial.print("ALT=");  Serial.println(gps.altitude.meters());

  
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);


  Serial.println("\n\n\n\n\n\n\n");
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}
