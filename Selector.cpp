//
// Created by chiic on 2021/11/30.
//
#include <cmath>

#include "Selector.h"
#include <wiringPi.h>

namespace tm_control{
    Selector::Selector(Decoder& dec, Multiplexer& mux): DC(dec), MUX(mux){
        if(wiringPiSetupGpio() < 0){
            return;
        }

        muxInit();
        decInit();
    }

    void Selector::muxInit() const{
        pinMode(MUX.a, OUTPUT);
        pinMode(MUX.b, OUTPUT);
        pinMode(MUX.c, OUTPUT);
        pinMode(MUX.d, OUTPUT);
    }

    void Selector::decInit() const {
        pinMode(DC.a, OUTPUT);
        pinMode(DC.b, OUTPUT);
        pinMode(DC.c, OUTPUT);
        pinMode(DC.enable, OUTPUT);
    }

    void Selector::muxSetValue(int value) const {
        digitalWrite(MUX.a, (value & 1000) >> 3);
        digitalWrite(MUX.b, (value & 0100) >> 2);
        digitalWrite(MUX.c, (value & 0010) >> 1);
        digitalWrite(MUX.d, (value & 0001) >> 0);
    }

    void Selector::decSetValue(int value) const {
        digitalWrite(DC.a, (value & 0100) >> 2);
        digitalWrite(DC.b, (value & 0010) >> 1);
        digitalWrite(DC.c, (value & 0001) >> 0);
    }

    void Selector::setMultiplex(int value) {
        int muxNum = floor(value / 16);
        int muxCh = value & 16;
        decSetValue(muxNum);
        muxSetValue(muxCh);
    }

    Selector::~Selector()= default;
}