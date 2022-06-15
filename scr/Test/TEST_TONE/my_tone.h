#ifndef BMP_H
#define BMP_H

#include <Adafruit_BMP085.h>
#include <vector>

class TONE
{
public:
    void start(){
        pinMode(12,OUTPUT);
        setupTimer();
    }

    void tone(long frequencyHz, long durationMs){
        setFrequency(frequencyHz);
        delay(durationMs);
        notone();
    }
    void notone(){
        timer = timerBegin(0, 80, true);//div 80
        timerAttachInterrupt(timer, &onTimer, true);
    }
private:
    const int tonePIN = 12;
    hw_timer_t* timer = NULL;
    bool value = true;
    int frequency = 20;

    void IRAM_ATTR onTimer() {
        value = !value;
        digitalWrite(tonePIN, value); 
    }

    void setupTimer() {
        // Use 1st timer of 4  - 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up 
        timer = timerBegin(0, 80, true);//div 80
        timerAttachInterrupt(timer, onTimer, true);
    }

    void setFrequency(long frequencyHz){
        timerAlarmDisable(timer);
        timerAlarmWrite(timer, 1000000l / frequencyHz, true);
        timerAlarmEnable(timer);
    }

    
};

#endif
