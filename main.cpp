#include <iostream>

#include "TouchMatrix.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    tm_control::Adc adc{
        0,
        0,
        2,
        1000000,
        0,
        8
    };

    tm_control::Driver drv{12,16,20,21};
    tm_control::Decoder dec{17,27,22,23};
    tm_control::Multiplexer mux{6,13,19,26};

    tm_control::SpiAdc adcControl((char*)"/dev/spidev0.0", adc);
    tm_control::Led ledControl(drv);
    tm_control::Selector selControl(dec, mux);
    tm_control::TouchMatrix tmControl(adcControl, selControl, ledControl);

    uint16_t raw = 0;
    for( int i = 0; i < 100; i++){
        tmControl.getRawValue(&raw, 0);
        std::cout << std::to_string(raw) << std::endl;
    }

    return 0;
}
