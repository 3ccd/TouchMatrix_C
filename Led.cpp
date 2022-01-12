//
// Created by user on 2021/12/01.
//

#include "Led.h"
#include <wiringPi.h>
#include <cstring>
#include <iostream>

namespace tm_control{

    Led::Led(Driver& drv) : DRV(drv){
        if(wiringPiSetup() < 0){
            std::cout << "led gpio error" << std::endl;
        }
        initBuffer();

        pinMode(DRV.sin, OUTPUT);
        pinMode(DRV.clk, OUTPUT);
        pinMode(DRV.rck, OUTPUT);
        pinMode(DRV.l_enable, OUTPUT);
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

    void Led::clearBuffer() {
        memset(buffer, 0, sizeof(buffer));
    }

    void Led::shift(int pin) {
        digitalWrite(pin, HIGH);
        delayMicroseconds(1);
        digitalWrite(pin, LOW);
    }

    void Led::sendBuffer() {
        setEnable(false);
        int chCount = DRV_CNT * DRV_CH;
        int bLen = chCount / 8;
        int chunk = 8;
        for(int i = chCount; i >= 0; i--){
            digitalWrite(DRV.sin, (buffer[int(i / chunk)] >> (i % chunk)) & 0b00000001);
            shift(DRV.clk);
        }
        shift(DRV.rck);
    }

    void Led::set(int num, bool output){
        int chunk = 8;
        if(int(num / chunk) >= bufferLength()) return;
        buffer[(int)(num / chunk)] |= (0b00000001 << (num % chunk));
    }

    void Led::setEnable(bool led_enable) const {
        int pin = 29;
        digitalWrite(pin, !led_enable);
    }

    Led::~Led() = default;
}
