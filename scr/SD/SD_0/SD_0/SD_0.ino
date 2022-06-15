
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define MISO  14
#define SCK  27
#define MOSI  26
#define CS  25

#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

#ifdef _ESP32_HAL_I2C_H_
#endif
String ans;
unsigned long Time;
SPIClass spi = SPIClass(VSPI);
//SoftwareSerial gpsSerial(17, 16); // RX, TX
//TinyGPSPlus gps;

static char HEADER[] = {
    "time_1,gyro_X,"
    "time_2,gyro_Y,"
    "time_3,gyro_Z,"
    "time_4,acceleration_X,"
    "time_5,acceleration_Y,"
    "time_6,acceleration_Z,"
    "time_7,Resultant g,"
    "time_8,Temperature,"
    "time_9,Pressure,"
    "time_10,Altitude,"
    "time_11,Pressure at sealevel (calculated),"
    "time_12,Altitude,"
    "time_13,Latitude,"
    "time_14,Longitude,"
    "time_15,GPS_Altitude"
};


void writeFile(fs::FS &fs, const char * path, const char * message){
  File file = fs.open(path, FILE_WRITE);
  if(!file){
    return;
  }
  file.print(message);
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
  File file = fs.open(path, FILE_APPEND);
  if(!file){
    return;
  }
  file.print(message);
  file.close();
}

void setup() {
//  bmp.begin();
  #ifdef _ESP32_HAL_I2C_H_
//  Wire.begin(SDA_PIN, SCL_PIN); 
  #else
  Wire.begin();
  #endif
  spi.begin(SCK, MISO, MOSI, CS);
  SD.begin(CS,spi,80000000);
  writeFile(SD, "/test.txt", HEADER);
}

void loop() {
    appendFile(SD, "/test.txt",ans.c_str());
}
