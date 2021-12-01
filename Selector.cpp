//
// Created by chiic on 2021/11/30.
//

#include "Selector.h"
#include <wiringPi.h>

namespace tm_control{
    Selector::Selector(Decorder dec, Multiplexer mux, LedDriver drv): DC(dec), MUX(mux), DRV(drv) {


    }

    void Selector::muxSetValue(int value) {
        
    }
}