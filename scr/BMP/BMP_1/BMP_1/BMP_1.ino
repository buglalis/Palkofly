#include <Adafruit_BMP085.h>
#define byte SBAS[24] = {0xB5, 0x62, 0x06, 0x16, 0x08, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x9F, 0xB5, 0x62, 0x06, 0x16, 0x00, 0x00, 0x1C, 0x5A};

Adafruit_BMP085 bmp;
long t;
int A = 30;
std::vector<float> buf;
float Zero;

void setup() {
  Serial.begin(115200);
  if (!bmp.begin(BMP085_ULTRAHIGHRES)) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  Zero = bmp.readAltitude();
  buf.resize(A,Zero);
}

template<class T>
void pop_front(std::vector<T> &v){
  if(v.size() > 0)
    v.erase(v.begin());
}

void loop() {
//      t = micros();
//      Serial.println(String(bmp.readAltitude()) + " " + String(micros() - t));
//      Serial.println(String(bmp.readAltitude()));
      float S = 0;
      buf.push_back(bmp.readAltitude());
      pop_front(buf);
      for(int i = 0; i < A; ++i) S += buf[i];
      Serial.println((String(S/A )));
}
