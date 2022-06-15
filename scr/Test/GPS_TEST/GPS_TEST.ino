#include <SoftwareSerial.h>
int RXPin = 3;                  // Указываем вывод подключения RX  
int TXPin = 4;                  // Указываем вывод подключения TX
 
int GPSBaud = 9600;             // Указываем скорость передачи с NEO-6M
 
SoftwareSerial ss(RXPin, TXPin); // Создайте последовательный связь под названием "gpsSerial"
 
void setup()
{
  Serial.begin(9600);           // Запускаем последовательный порт с ПК на скорости 9600
  ss.begin(GPSBaud);     // Запустите последовательный порт с NEO-6M на скорости 9600
}
 
void loop()
{
  while (ss.available() > 0)
  Serial.write(ss.read());
}
