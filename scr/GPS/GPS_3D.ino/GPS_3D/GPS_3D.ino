#include <SoftwareSerial.h>
//#include <TinyGPSPlus.h>
//
////// The serial connection to the GPS module
SoftwareSerial gps(16, 17, false, 256);
//
int bod = 9600;
//int bod = 115200;
void setup() {
  Serial.begin(bod);
  gps.begin(bod);
}


void loop() 
{
  while (gps.available() > 0)
  {
    Serial.write(gps.read());
  }
  while (Serial.available() > 0)
  {
    gps.write(Serial.read());
  }
}

//void setup()
//{
//  Serial.begin(9600);
//  Serial.end();
//  Serial1.begin(115200);
//  
//}
//
//void loop(){
//  
//  Serial1.println(String(123));
//}
