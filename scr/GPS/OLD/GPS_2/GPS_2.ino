//// 
////#include <SoftwareSerial.h>
////
////// The serial connection to the GPS module
////SoftwareSerial ss(4, 3);
////
////void setup(){
////  Serial.begin(9600);
////  ss.begin(9600);
////}
////
////void loop(){
////  while (ss.available() > 0){
////    // get the byte data from the GPS
////    byte gpsData = ss.read();
////    Serial.write(gpsData);
////  }
////}
//
// 

//
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
//
////// The serial connection to the GPS module
//SoftwareSerial ss(16, 17);
////
//void setup(){
//  Serial.begin(115200);
//  ss.begin(9600);
//}
//
//void loop(){
//  while (ss.available() > 0){
//    // get the byte data from the GPS
//    byte gpsData = ss.read();
//    Serial.write(gpsData);
//  }
//}




//



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
  {
//    Serial.println(gps.altitude.meters());
  
    Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
    Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
    Serial.print("ALT=");  Serial.println(gps.altitude.meters());
  }

  
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

//  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
//  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
//  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
//  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
//  printInt(gps.location.age(), gps.location.isValid(), 5);
//  printDateTime(gps.date, gps.time);
//  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
//  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
//  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
//  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);




//  printInt(gps.charsProcessed(), true, 6);
//  printInt(gps.sentencesWithFix(), true, 10);
//  printInt(gps.failedChecksum(), true, 9);
//  Serial.println("\n\n\n\n\n\n\n");
  
  smartDelay(1000);

//  if (millis() > 5000 && gps.charsProcessed() < 10)
//    Serial.println(F("No GPS data received: check wiring"));
}






// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
