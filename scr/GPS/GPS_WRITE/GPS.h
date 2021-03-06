#include <SoftwareSerial.h>
//#include "SD_adapter.h"

//#define filename "gps_data/data_gps.txt"
#define filename "/data_gps.txt"
SoftwareSerial ss(16, 17, false, 256);
byte INIT[116] = {0xB5, 0x62, 0x0A, 0x04, 0x00, 0x00, 0x0E, 0x34, 0xB5, 0x62, 0x0A, 0x04, 0x64, 0x00, 0x31, 0x2E, 0x30, 0x30, 0x20, 0x28, 0x35, 0x39, 0x38, 0x34, 0x32, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x37, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x50, 0x52, 0x4F, 0x54, 0x56, 0x45, 0x52, 0x20, 0x31, 0x34, 0x2E, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x50, 0x53, 0x3B, 0x53, 0x42, 0x41, 0x53, 0x3B, 0x47, 0x4C, 0x4F, 0x3B, 0x51, 0x5A, 0x53, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x71, 0xB2};
byte RESET[31] = {0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x03, 0x1B, 0x9A, 0xB5, 0x62, 0x05, 0x01, 0x02, 0x00, 0x06, 0x09, 0x17, 0x40};
byte GNSS[116] = {0xB5, 0x62, 0x06, 0x3E, 0x24, 0x00, 0x00, 0x00, 0x16, 0x04, 0x00, 0x04, 0xFF, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x01, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x08, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0xA5, 0x39, 0xB5, 0x62, 0x06, 0x3E, 0x00, 0x00, 0x44, 0xD2, 0xB5, 0x62, 0x05, 0x01, 0x02, 0x00, 0x06, 0x3E, 0x4C, 0x75, 0xB5, 0x62, 0x06, 0x3E, 0x24, 0x00, 0x00, 0x16, 0x16, 0x04, 0x00, 0x04, 0xFF, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x08, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB7, 0x07, 0xB5, 0x62, 0x05, 0x01, 0x02, 0x00, 0x06, 0x3E, 0x4C, 0x75};
byte NAV5[116] = {0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0xE8, 0xB5, 0x62, 0x06, 0x24, 0x00, 0x00, 0x2A, 0x84, 0xB5, 0x62, 0x05, 0x01, 0x02, 0x00, 0x06, 0x24, 0x32, 0x5B, 0xB5, 0x62, 0x06, 0x24, 0x24, 0x00, 0xFF, 0xFF, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x05, 0x00, 0xFA, 0x00, 0xFA, 0x00, 0x64, 0x00, 0x2C, 0x01, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0xE8, 0xB5, 0x62, 0x05, 0x01, 0x02, 0x00, 0x06, 0x24, 0x32, 0x5B};
byte RATE[46] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x64, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7A, 0x12, 0xB5, 0x62, 0x06, 0x08, 0x00, 0x00, 0x0E, 0x30, 0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x64, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7A, 0x12, 0xB5, 0x62, 0x05, 0x01, 0x02, 0x00, 0x06, 0x08, 0x16, 0x3F}; 
byte SBAS[24] = {0xB5, 0x62, 0x06, 0x16, 0x08, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x9F, 0xB5, 0x62, 0x06, 0x16, 0x00, 0x00, 0x1C, 0x5A};
byte PRT[37] = {0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0xC2, 0x01, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBC, 0x5E, 0xB5, 0x62, 0x06, 0x00, 0x01, 0x00, 0x01, 0x08, 0x22};
byte TP5[49] = {0xB5, 0x62, 0x06, 0x31, 0x20, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x9A, 0x99, 0x99, 0x19, 0x00, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00, 0x40, 0x84, 0xB5, 0x62, 0x06, 0x31, 0x01, 0x00, 0x00, 0x38, 0xE5};

//void write_data(byte* arr)
//{
//   for(int i = 0; i < sizeof(arr); ++i)
//    gps.write(arr[i]);
//}

void set_GPS()
{
  for(auto v: INIT) ss.write(v);
  for(auto v: RESET) ss.write(v);
  for(auto v: TP5) ss.write(v);
  for(auto v: GNSS) ss.write(v);
  for(auto v: NAV5) ss.write(v);
  for(auto v: RATE) ss.write(v);
  for(auto v: SBAS) ss.write(v);
  for(auto v: PRT) ss.write(v);
  
  
}
