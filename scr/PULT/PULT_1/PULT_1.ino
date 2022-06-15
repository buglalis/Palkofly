byte PWM_PIN = 3;
 
int pwm_value;
 
void setup() {
  pinMode(PWM_PIN, INPUT);
  Serial.begin(250000);
}
 
void loop() {
  pwm_value = pulseIn(PWM_PIN, HIGH);
  Serial.println(pwm_value);
}


//int pulse = 0;
//unsigned long ch[7], t[8];
//
//void setup()
//{
//  PCICR != (1 << PCIE0);
//  PCMSK0 != (1 << PCINT0);
//  Serial.begin(9600);
//}
//
//void loop()
//{
//    
//}
//
//ISR(PCINT0_vect){
//  if(PINB & B00000001){
//    t[pulse] = micros();
//    switch (pulse){
//      case 1:
//        ch[1] = t[1] - t[0];
//        pulse++;
//        if(ch[1] > 3000){
//          t[0] = t[1];
//          pulse = 1;
//        }
//        break;
//      case 2:
//        ch[2] = t[2] - t[1];
//        pulse++;
//        break;
//    }
//  }
//}


//#include <PPMReader.h>
//#include <InterruptHandler.h>
//#include <Servo.h>
//int interruptPin = 3;                                                  //  пин приемника
//int channelAmount = 8;                                                 //  число каналов (max 8 для PPM)
//PPMReader ppm(interruptPin, channelAmount);
//
//#define svr1 5
//#define svr2 6
//#define svr3 7
//#define svr4 8
//#define svr5 9
//#define svr6 10
//#define svr7 11
//#define svr8 12
//
//Servo Srv_1;
//Servo Srv_2;
//Servo Srv_3;
//Servo Srv_4;
//Servo Srv_5;
//Servo Srv_6;
//Servo Srv_7;
//Servo Srv_8;
//
//#define ch1   value[1]
//#define ch2   value[2]
//#define ch3   value[3]
//#define ch4   value[4]
//#define ch5   value[5]
//#define ch6   value[6]
//#define ch7   value[7]
//#define ch8   value[8]
//unsigned int value[9];
//
//void setup(){//Serial.begin(115200);
//  Srv_1.attach(svr1); 
//   Srv_2.attach(svr2); 
//    Srv_3.attach(svr3); 
//     Srv_4.attach(svr4); 
//      Srv_5.attach(svr5); 
//       Srv_6.attach(svr6); 
//        Srv_7.attach(svr7); 
//         Srv_8.attach(svr8); 
//  }
//
//void read_ppm(){
//   unsigned long temp;
//   for (int channel = 1; channel <= channelAmount; ++channel)                     //  ВЫВОД ВСЕХ КАНАЛОВ В SERIAL
//    {
//     if(channel==3) {value[channel] = (unsigned int)ppm.rawChannelValue(channel); //  FS настроен на стик газа CH3
//     }else{                                                             
//     value[channel] = (unsigned int)ppm.latestValidChannelValue(channel, 0);}
//  
//    }
//   }
//
//void run_ppm(){
//     Srv_1.write(ch1); 
//      Srv_2.write(ch2); 
//       Srv_3.write(ch3);
//        Srv_4.write(ch4); 
//         Srv_5.write(ch5);  
//          Srv_6.write(ch6); 
//           Srv_7.write(ch7);  
//            Srv_8.write(ch8); 
//}
//
//void loop()
//{
//    read_ppm();
//    run_ppm();
//    delay(15);
//}


//#include "PPMReader.h"
//
//// PPMReader(pin, interrupt)
//PPMReader ppmReader(2, 0);
//
//void setup()
//{
//  Serial.begin(115200);
//}
//
//void loop()
//{
//  static int count;
//  while (ppmReader.get(count) != 0) { //print out the servo values
//      Serial.print(ppmReader.get(count));
//      Serial.print("  ");
//      count++;
//  }
//  count = 0;
//  delay(500);
//}
