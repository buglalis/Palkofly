#include <vector>
void myupdate(int* arr)
{
  int S = 0;
  for(int i = 0; i < sizeof(arr); ++i)
  {
//    S
  }
}



#include <MPU9250_asukiaaa.h>

#define SDA_PIN 21
#define SCL_PIN 22

#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 21
#define SCL_PIN 22
#endif

MPU9250_asukiaaa mySensor;

void setup() {
while(!Serial);

Serial.begin(115200);
Serial.println("started");

#ifdef _ESP32_HAL_I2C_H_
// for esp32
Wire.begin(SDA_PIN, SCL_PIN); //sda, scl
#else
Wire.begin();
#endif

mySensor.setWire(&Wire);

//mySensor.beginAccel();
//mySensor.beginMag();
mySensor.beginGyro();

// you can set your own offset for mag values
// mySensor.magXOffset = -100;
// mySensor.magYOffset = -0.36;
// mySensor.magZOffset = -10;
// mySensor.gyroXOffset = 0.05;
std::vector<int> x(10);
int* y = new int[10];
int* z = new int[10];

}

void loop() {
//mySensor.accelUpdate();
//Serial.println("print accel values");
//Serial.println("accelX: " + String(mySensor.accelX()));
//Serial.println("accelY: " + String(mySensor.accelY()));
//Serial.println("accelZ: " + String(mySensor.accelZ()));
//Serial.println("accelSqrt: " + String(mySensor.accelSqrt()));
mySensor.gyroUpdate();
Serial.println("X " + String(mySensor.gyroX()));
Serial.println("Y " + String(mySensor.gyroY()));
Serial.println("Z " + String(mySensor.gyroZ()) + "\n\n\n\n\n\n\n\n\n\n\n\n");

//mySensor.magUpdate();
//Serial.println("print mag values");
//Serial.println("magX: " + String(mySensor.magX()));
//Serial.println("maxY: " + String(mySensor.magY()));
//Serial.println("magZ: " + String(mySensor.magZ()));
//Serial.println("horizontal direction: " + String(mySensor.magHorizDirection()));

//Serial.println("at " + String(millis()) + "ms");
delay(100);
}
