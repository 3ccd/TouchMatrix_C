#include <iostream>

#include "SpiAdc.h"

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
    tm_control::SpiAdc spiAdc("/dev/spidev0.0", adc);
    return 0;
}
