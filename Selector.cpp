//
// Created by chiic on 2021/11/30.
//
#include <cmath>

#include "Selector.h"
#include <wiringPi.h>
#include <iostream>

namespace tm_control{
    Selector::Selector(Decoder& dec, Multiplexer& mux): DC(dec), MUX(mux){
        if(wiringPiSetup() < 0){
            std::cout << "selector gpio error" << std::endl;
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
        digitalWrite(DC.enable, TRUE);
    }

    void Selector::muxSetValue(int value) const {
        digitalWrite(MUX.a, (bool)((value & 0b1000) >> 3));
        digitalWrite(MUX.b, (bool)((value & 0b0100) >> 2));
        digitalWrite(MUX.c, (bool)((value & 0b0010) >> 1));
        digitalWrite(MUX.d, (bool)((value & 0b0001) >> 0));
    }

    void Selector::decSetValue(int value) const {
        digitalWrite(DC.c, (bool)((value & 0b0100) >> 2));
        digitalWrite(DC.b, (bool)((value & 0b0010) >> 1));
        digitalWrite(DC.a, (bool)((value & 0b0001) >> 0));
    }

    void Selector::setMultiplex(int value) {
        int muxNum = floor(value / 16);
        int muxCh = value % 16;
        decSetValue(muxNum);
        muxSetValue(muxCh);
    }

    Selector::~Selector()= default;
}