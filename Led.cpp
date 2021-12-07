//
// Created by user on 2021/12/01.
//

#include "Led.h"
#include <wiringPi.h>

namespace tm_control{

    Led::Led(Driver& drv) : DRV(drv){
        if(wiringPiSetupGpio() < 0){
            return;
        }
        initBuffer();

        pinMode(DRV.sin, OUTPUT);
        pinMode(DRV.clk, OUTPUT);
        pinMode(DRV.rck, OUTPUT);
        pinMode(DRV.enable, OUTPUT);
    }

    int Led::bufferLength() {
        int length = sizeof(buffer) / sizeof(buffer[0]);
        return length;
    }

    void Led::initBuffer() {
        for(int i = 0; i < bufferLength(); i++ ){
            buffer[i] = 0;
        }
    }

    void Led::shift(int pin) {
        digitalWrite(pin, HIGH);
        delayMicroseconds(1);
        digitalWrite(pin, LOW);
    }

    void Led::sendBuffer() {
        digitalWrite(DRV.enable, HIGH);
        int chCount = DRV_CNT * DRV_CH;
        int bLen = bufferLength();
        int chunk = sizeof(unsigned char);
        for(int i = 0; i < chCount; i++){
            digitalWrite(DRV.sin, buffer[(bLen - 1) - int(i / chunk)] >> i % chunk);
            shift(DRV.clk);
        }
        shift(DRV.rck);
        digitalWrite(DRV.enable, LOW);
    }

    void Led::set(int num, bool output){
        int chunk = sizeof(unsigned char);
        if(int(num / chunk) >= bufferLength()) return;
        buffer[int(num / chunk)] |= (0b10000000 >> (num % chunk));
    }

    Led::~Led() = default;
}
