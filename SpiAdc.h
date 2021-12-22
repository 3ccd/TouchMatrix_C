//
// Created by chiic on 2021/12/04.
//

#ifndef TOUCHMATRIX_SPIADC_H
#define TOUCHMATRIX_SPIADC_H

#include "Singleton.h"

namespace tm_control{

    struct Adc{
        int bus;
        int chip_select;
        int spi_mode;
        int spi_speed_hz;
        int spi_delay_usecs;
        int spi_bits;
    };

    class SpiAdc{
    private:
        const Adc& ADC;
        char *m_spidev;
        int fd;
        bool isOpen;

        int beginSpi();

    public:
        SpiAdc(char *p_spidev, Adc& adc);
        ~SpiAdc();
    };
}



#endif //TOUCHMATRIX_SPIADC_H
