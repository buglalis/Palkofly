#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include <Adafruit_BMP085.h>
#include <MPU9250_WE.h>
#include <Wire.h>


#define MPU9250_ADDR 0x68

#include "FS.h"
#include "SD.h"
#include "SPI.h"

Adafruit_BMP085 bmp;
#define SDA_PIN 21
#define SCL_PIN 22

#define MISO  14
#define SCK  27
#define MOSI  26
#define CS  25



#ifdef _ESP32_HAL_I2C_H_
#endif

MPU9250_WE myMPU9250 = MPU9250_WE(MPU9250_ADDR);
String ans;
const char sep =',';
unsigned long long Time;
unsigned long Time_1,Time_2;
xyzFloat gValue;
float resultantG;
xyzFloat gyr;
SPIClass spi = SPIClass(VSPI);
SoftwareSerial ass(16,17);
TinyGPSPlus gps;

static char HEADER[] = {
    "time_1.1,time_1.2,gyro_X,"
    "time_2.1,time_2.2,gyro_Y,"
    "time_3.1,time_3.2,gyro_Z,"
    "time_4.1,time_4.2,acceleration_X,"
    "time_5.1,time_5.2,acceleration_Y,"
    "time_6.1,time_6.2,acceleration_Z,"
    "time_7.1,time_7.2,Resultant g,"
    "time_8.1,time_8.2,Temperature,"
    "time_9.1,time_9.2,Pressure,"
    "time_10.1,time_10.2,Altitude,"
    "time_11.1,time_11.2,Pressure at sealevel (calculated),"
    "time_12.1,time_12.2,Latitude,"
    "time_13.1,time_13.2,Longitude,"
    "time_14.1,time_14.2,GPS_Altitude,"
    "time_15.1,time_15.2,speed,"
    "time_16.1,time_16.2,course,time_17.1,time_17.2"
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
   pinMode(12,OUTPUT);
   digitalWrite(12,HIGH);
   delay(100);
   digitalWrite(12,LOW);
  bmp.begin();
  ass.begin(9600);
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
  
  writeFile(SD, "/test.txt", HEADER);
  while  (!gps.altitude.isUpdated()){while (ass.available() > 0){gps.encode(ass.read());}}
    digitalWrite(12,HIGH);
    delay(1000);
    digitalWrite(12,LOW);
    }

void loop() {
  gValue = myMPU9250.getGValues();
  resultantG = myMPU9250.getResultantG(gValue);
  gyr = myMPU9250.getGyrValues();
  while (ass.available() > 0){
    gps.encode(ass.read());
  }
  ans="\n";
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gyr.x)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gyr.y)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gyr.z)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gValue.x)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gValue.y)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gValue.z)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(resultantG)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(bmp.readTemperature())+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(bmp.readPressure())+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(bmp.readAltitude())+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(bmp.readSealevelPressure())+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gps.location.lat(),6)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gps.location.lng(),6)+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gps.altitude.meters())+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gps.speed.mps())+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2)+sep+String(gps.course.deg())+sep;
  Time=micros();Time_1=Time/1000000000;Time_2=Time%1000000000;ans+=String(Time_1)+sep+String(Time_2);

  
  appendFile(SD, "/test.txt",ans.c_str());

}
