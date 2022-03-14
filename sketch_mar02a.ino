




//#######################################################
//#include <Adafruit_BMP085.h>
////
//#define LED 2
//Adafruit_BMP085 pressure;
//
//#define ALTITUDE 390.0
//
//void setup() {
//  pinMode(LED, OUTPUT);
//  Serial.begin(9600);
//  pressure.begin();
//}
//
//void loop() {
//
////  
//  Serial.println("hvgyyvg");
//  delay(250);
//  digitalWrite(LED, HIGH);
//  delay(250);
//  digitalWrite(LED, LOW);
//}
//#######################################################



//#include <Adafruit_BMP085.h>
//
///*************************************************** 
//  This is an example for the BMP085 Barometric Pressure & Temp Sensor
//  Designed specifically to work with the Adafruit BMP085 Breakout 
//  ----> https://www.adafruit.com/products/391
//  These pressure and temperature sensors use I2C to communicate, 2 pins
//  are required to interface
//  Adafruit invests time and resources providing this open source code, 
//  please support Adafruit and open-source hardware by purchasing 
//  products from Adafruit!
//  Written by Limor Fried/Ladyada for Adafruit Industries.  
//  BSD license, all text above must be included in any redistribution
// ****************************************************/
//
//// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
//// Connect GND to Ground
//// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
//// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
//// EOC is not used, it signifies an end of conversion
//// XCLR is a reset pin, also not used here
//
//Adafruit_BMP085 bmp;
//  
//void setup() {
//  Serial.begin(9600);
//  if (!bmp.begin()) {
//  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
//  while (1) {}
//  }
//}
//  
//void loop() {
//    Serial.print("Temperature = ");
//    Serial.print(bmp.readTemperature());
//    Serial.println(" *C");
//    
//    Serial.print("Pressure = ");
//    Serial.print(bmp.readPressure());
//    Serial.println(" Pa");
//    
//    // Calculate altitude assuming 'standard' barometric
//    // pressure of 1013.25 millibar = 101325 Pascal
//    Serial.print("Altitude = ");
//    Serial.print(bmp.readAltitude());
//    Serial.println(" meters");
//
//    Serial.print("Pressure at sealevel (calculated) = ");
//    Serial.print(bmp.readSealevelPressure());
//    Serial.println(" Pa");
//
//  // you can get a more precise measurement of altitude
//  // if you know the current sea level pressure which will
//  // vary with weather and such. If it is 1015 millibars
//  // that is equal to 101500 Pascals.
//    Serial.print("Real altitude = ");
//    Serial.print(bmp.readAltitude(101500));
//    Serial.println(" meters");
//    
//    Serial.println();
//    delay(500);
//}




#include "mpu9250.h"

/* Mpu9250 object */
bfs::Mpu9250 imu;

void setup() {
  /* Serial to display data */
  Serial.begin(9600);
  Serial.println("jhgjhgj");
  while(!Serial) {}
  /* Start the I2C bus */
  Wire.begin();
  Wire.setClock(400000);
  /* I2C bus,  0x68 address */
  imu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);
  /* Initialize and configure IMU */
  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {}
  }
  Serial.println("jhgjhgj");
  /* Set the sample rate divider */
  if (!imu.ConfigSrd(19)) {
    Serial.println("Error configured SRD");
    while(1) {}
  }
}

void loop() {

  
  /* Check if data read */
  if (imu.Read()) {
    Serial.print(imu.new_imu_data());
    Serial.print("\t");
    Serial.print(imu.new_mag_data());
    Serial.print("\t");
    Serial.print(imu.accel_x_mps2());
    Serial.print("\t");
    Serial.print(imu.accel_y_mps2());
    Serial.print("\t");
    Serial.print(imu.accel_z_mps2());
    Serial.print("\t");
    Serial.print(imu.gyro_x_radps());
    Serial.print("\t");
    Serial.print(imu.gyro_y_radps());
    Serial.print("\t");
    Serial.print(imu.gyro_z_radps());
    Serial.print("\t");
    Serial.print(imu.mag_x_ut());
    Serial.print("\t");
    Serial.print(imu.mag_y_ut());
    Serial.print("\t");
    Serial.print(imu.mag_z_ut());
    Serial.print("\t");
    Serial.print(imu.die_temp_c());
    Serial.print("\n");
  }
}
