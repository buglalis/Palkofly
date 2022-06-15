#ifndef BMP_H
#define BMP_H

#include <Adafruit_BMP085.h>
#include <vector>

class BMP
{
public:
    BMP(short size) : buf(size) {};
    void start(){
        while(!bmp.begin(BMP085_ULTRAHIGHRES)){};
        Zero = bmp.readAltitude();
        buf.resize(A,Zero);
    }
    
    void update(){
        float S = 0;
        buf.push_back(bmp.readAltitude());
        pop_front();
        for(int i = 0; i < A; ++i) S += buf[i];
    }
    
    float get_altitude(){
        return S/buf_size;
    }
private:
    Adafruit_BMP085 bmp;
    std::vector<float> buf;
    float Zero;
    float S;
    short buf_size;

    void pop_front(){
        buf.erase(buf.begin());
    }
};

#endif
