#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

// The serial connection to the GPS module
SoftwareSerial ss(16, 17);

void setup(){
 Serial.begin(115200);
 ss.begin(9600);
}

void loop(){
 while (ss.available() > 0){
   // get the byte data from the GPS
   byte gpsData = ss.read();
   Serial.write(gpsData);
 }
}
