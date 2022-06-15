#include "GPS.h"
#include <TinyGPSPlus.h>
#include "my_tone.hpp"
// INITIALIZATION GLOBAL VARIABLES
int bod = 9600;
TinyGPSPlus gps;

void setup() {
  pinMode(tonePIN, OUTPUT);
  setupTimer();

  ss.begin(bod);
  set_GPS();
  ss.begin(115200);
  while  (!gps.altitude.isUpdated()){while (ss.available() > 0){gps.encode(ss.read());}}
  tone(500,100);
  
  
}

void loop()
{
  while (ss.available() > 0)
  {
    Serial.write(ss.read());
  }
  while (Serial.available() > 0)
  {
    ss.write(Serial.read());
  }
}
