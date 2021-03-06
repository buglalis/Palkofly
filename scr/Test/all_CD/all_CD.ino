#include "GPS.h"
#include "my_tone.hpp"

#include <EEPROM.h>
#define EEPROM_SIZE 1
int filenumber;
String filestr="/data_";
const char* filename;

#include <SoftwareSerial.h>
#include <Adafruit_BMP085.h>
#include <MPU9250_WE.h>
#include <Wire.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define MPU9250_ADDR 0x68
#define SDA_PIN 21
#define SCL_PIN 22

#define MISO 14
#define SCK 27
#define MOSI 26
#define CS 25

#ifdef _ESP32_HAL_I2C_H_
#endif

Adafruit_BMP085 bmp;
MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);
String ans;
const char sep =',';
xyzFloat gValue;
float resultantG;
xyzFloat gyr;
SPIClass spi = SPIClass(VSPI);
//SoftwareSerial ass(16,17,false,256);


static char HEADER[] = {
    "time_1,gyro_X,"
    "time_2,gyro_Y,"
    "time_3,gyro_Z,"
    "time_4,acceleration_X,"
    "time_5,acceleration_Y,"
    "time_6,acceleration_Z,"
    "time_7,Resultant g,"
    "time_8,Altitude,"
    "time_9,Latitude,"
    "time_10,Longitude,"
    "time_11,GPS_Altitude,"
    "time_12,speed,"
    "time_13,course,time_14"
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
  EEPROM.begin(EEPROM_SIZE);
  filenumber = EEPROM.read(0);
  if ((filenumber<0) or (filenumber>256)){ filenumber=0; }
  filestr+=String(filenumber)+".txt";
  filename=filestr.c_str();
  
  // squeaker
  pinMode(12,OUTPUT);
  setupTimer();
  tone(500,100);
  
 
  bmp.begin();
  #ifdef _ESP32_HAL_I2C_H_
  Wire.begin(SDA_PIN, SCL_PIN); 
  #else
  Wire.begin();
  #endif
  spi.begin(SCK, MISO, MOSI, CS);
  SD.begin(CS,spi,80000000);
  myMPU9250.init();
  delay(1000);
  myMPU9250.autoOffsets();
  myMPU9250.setAccRange(MPU9250_ACC_RANGE_16G);
  myMPU9250.enableAccDLPF(true);
  myMPU9250.setAccDLPF(MPU9250_DLPF_6);
  myMPU9250.enableGyrDLPF();
  myMPU9250.setSampleRateDivider(99);
  myMPU9250.setGyrRange(MPU9250_GYRO_RANGE_2000);

  // GPS
  start_GPS();
  tone(200,300);
  
  // Create new fly-log
  writeFile(SD, filename, HEADER);
  EEPROM.write(0, filenumber+1);
  EEPROM.commit();
}
  

void loop() {
  gValue = myMPU9250.getGValues();
  resultantG = myMPU9250.getResultantG(gValue);
  gyr = myMPU9250.getGyrValues();
  while (ss.available() > 0){
    gps.encode(ss.read());
  }
  ans="\n";
  ans+=String(micros())+sep;
  ans+=String(gyr.x)+sep;ans+=String(micros())+sep;
  ans+=String(gyr.y)+sep;ans+=String(micros())+sep;
  ans+=String(gyr.z)+sep;ans+=String(micros())+sep;
  ans+=String(gValue.x)+sep;ans+=String(micros())+sep;
  ans+=String(gValue.y)+sep;ans+=String(micros())+sep;
  ans+=String(gValue.z)+sep;ans+=String(micros())+sep;
  ans+=String(resultantG)+sep;ans+=String(micros())+sep;
  ans+=String(bmp.readAltitude()) + sep;ans+=String(micros())+sep;
  
  ans+=String(gps.location.lat(),6)+sep;ans+=String(micros())+sep;
  ans+=String(gps.location.lng(),6)+sep;ans+=String(micros())+sep;
  ans+=String(gps.altitude.meters())+sep;ans+=String(micros())+sep;
  
  ans+=String(gps.speed.mps())+sep;ans+=String(micros())+sep;
  ans+=String(gps.course.deg())+sep;ans+=String(micros());
  
  appendFile(SD, filename, ans.c_str());

}
