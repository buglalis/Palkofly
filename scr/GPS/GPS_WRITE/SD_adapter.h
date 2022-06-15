#ifndef SD_ADAPTER_H
#define SD_ADAPTER_H

#include "FS.h"
#include "SD.h"
#include "SPI.h"

///////////////////////////////////////////
#define MISO 14
#define SCK 27
#define MOSI 26
#define CS 25

SPIClass spi = SPIClass(VSPI);

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
///////////////////////////////////////////
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

void readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

#endif


//void setup() {
//  spi.begin(SCK, MISO, MOSI, CS);
//  SD.begin(CS,spi,80000000);
//  writeFile(SD, filename, HEADER);
//
//}
