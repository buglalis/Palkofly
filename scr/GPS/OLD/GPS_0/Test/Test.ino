#include <Wire.h>
const int MPU = 0x68; // MPU6050 I2C адрес
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;
void setup() {
  Serial.begin(19200);
  Wire.begin();                      // Инициализировать связь
  Wire.beginTransmission(MPU);       // Начать связь с MPU6050 // MPU = 0x68
  Wire.write(0x6B);                  // обращаемся к регистру 6B
  Wire.write(0x00);                  //  сброс - поместите 0 в регистр 6B
  Wire.endTransmission(true);        //закончить передачу
  /*
  // Настройка чувствительности акселерометра - полный диапазон шкалы (по умолчанию +/- 2g)
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  //обращаемся к регистру ACCEL_CONFIG (1C hex)
  Wire.write(0x10);                  //Установить биты регистра как 00010000 (диапазон полной шкалы +/- 8g)
  Wire.endTransmission(true);
  // Настроить чувствительность гироскопа - полный диапазон шкалы (по умолчанию +/- 250 град / с)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);                   // Обращаемся к регистру GYRO_CONFIG (1B hex)
  Wire.write(0x10);                   // Установить биты регистра как 00010000 (полная шкала 1000 град / с)
  Wire.endTransmission(true);
  delay(20);
  */
  // Вызов этой функции, покажет значения ошибок IMU для вашего модуля
  calculate_IMU_error();
  delay(20);
}
void loop() {
 // === Считать данные акселерометра === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Начинаем с регистра 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Чтение всех 6 регистров, значение каждой оси сохраняется в 2 регистрах
// Для диапазона + -2g нам нужно разделить необработанные значения на 16384 в соответствии с datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // Значение по оси X
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Значение по оси Y
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Значение по оси Z
 // Расчет крена и тангажа по данным акселерометра
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58;
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58;
  // === Считываем данные гироскопа === //
  previousTime = currentTime;        // Предыдущее время сохраняется до фактического чтения
  currentTime = millis();           // Текущее время Фактическое время чтения
  elapsedTime = (currentTime - previousTime) / 1000; // Разделим на 1000, чтобы получить секунды
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Адрес первого регистра данных гироскопа 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Чтение всех 4 регистров, значение каждой оси сохраняется в 2 регистрах
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // Для диапазона 250 градусов / с мы должны сначала разделить необработанное значение на 131.0, согласно datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
 // Корректируем выходы с вычисленными значениями ошибок
  GyroX = GyroX + 0.56; // GyroErrorX ~(-0.56)
  GyroY = GyroY - 2; // GyroErrorY ~(2)
  GyroZ = GyroZ + 0.79; // GyroErrorZ ~ (-0.8)
 // В настоящее время необработанные значения выражаются в градусах в секунду, град / с, поэтому нам нужно умножить на sendonds (s), чтобы получить угол в градусах
  gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
  gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  yaw =  yaw + GyroZ * elapsedTime;
// Дополнительный фильтр - объединить значения угла акселерометра и гироскопа
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
  
// Выводим значения на серийный монитор
  Serial.print(roll);
  Serial.print("/");
  Serial.print(pitch);
  Serial.print("/");
  Serial.println(yaw);
}
void calculate_IMU_error() {
// Мы можем вызвать эту функцию в разделе setup(), чтобы вычислить ошибку данных акселерометра и гироскопа. Отсюда мы получим значения ошибок, используемые в приведенных выше уравнениях, напечатанные на последовательном мониторе.
   // Обратите внимание, что мы должны разместить датчик плоско, чтобы получить правильные значения, чтобы затем мы могли считать правильные значения
   // Считываем значения акселерометра 200 раз
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    // Sum all readings
    AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    c++;
  }
  // Разделим сумму на 200, чтобы получить значение ошибки
  AccErrorX = AccErrorX / 200;
  AccErrorY = AccErrorY / 200;
  c = 0;
  // Считываем значения гироскопа 200 раз
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorX = GyroErrorX + (GyroX / 131.0);
    GyroErrorY = GyroErrorY + (GyroY / 131.0);
    GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
    c++;
  }
// Разделим сумму на 200, чтобы получить значение ошибки
  GyroErrorX = GyroErrorX / 200;
  GyroErrorY = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;
 // Выводим значения ошибок на Serial Monitor
  Serial.print("AccErrorX: ");
  Serial.println(AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(AccErrorY);
  Serial.print("GyroErrorX: ");
  Serial.println(GyroErrorX);
  Serial.print("GyroErrorY: ");
  Serial.println(GyroErrorY);
  Serial.print("GyroErrorZ: ");
  Serial.println(GyroErrorZ);
}
