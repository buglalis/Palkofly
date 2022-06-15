#include <MPU9250_asukiaaa.h>

#define SDA_PIN 21
#define SCL_PIN 22

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
mySensor.beginGyro();
}

void loop() {
mySensor.gyroUpdate();
Serial.println("X " + String(mySensor.gyroX()));
Serial.println("Y " + String(mySensor.gyroY()));
Serial.println("Z " + String(mySensor.gyroZ()) + "\n\n\n\n\n\n\n\n\n\n\n\n");
delay(100);
}
