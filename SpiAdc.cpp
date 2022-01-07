//
// Created by chiic on 2021/12/04.
//

#include "SpiAdc.h"
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <iostream>
#include <cerrno>

namespace tm_control {

    SpiAdc::SpiAdc(char *p_spidev, Adc &adc) : ADC(adc) {
        m_spidev = nullptr;
        if (p_spidev != nullptr) {
            m_spidev = (char *) malloc(strlen(p_spidev) + 1);
            if (m_spidev != nullptr) strcpy(m_spidev, p_spidev);
        } else {
            return;
        }

        int ret = beginSpi();
        if(ret < 0) {
            std::cout << "spi error " << std::to_string(ret) << std::endl;
            printf("print error string by strerror: %s\n", strerror(errno));
        }
    }

    int SpiAdc::beginSpi() {
        fd = open(m_spidev, O_RDWR);
        if (fd < 0) {
            isOpen = false;
            return -1;
        }

        int mode = ADC.spi_mode | SPI_3WIRE;
        if(ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0){
            close(fd);
            isOpen = false;
            return -2;
        }
        if(ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0){
            close(fd);
            isOpen = false;
            return -3;
        }
        if(ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &ADC.spi_bits) < 0){
            close(fd);
            isOpen = false;
            return -4;
        }
        if(ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &ADC.spi_bits) < 0){
            close(fd);
            isOpen = false;
            return -5;
        }
        if(ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &ADC.spi_speed_hz) < 0){
            close(fd);
            isOpen = false;
            return -6;
        }
        if(ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &ADC.spi_speed_hz) < 0){
            close(fd);
            isOpen = false;
            return -7;
        }
        isOpen = true;
        return 0;
    }

    int SpiAdc::read() {
        uint8_t	rxbuf[4096];
        uint16_t value;
        int len = 2;

        memset(rxbuf, 0, sizeof rxbuf);

        ::read(fd, &rxbuf[0], len);

        value = (rxbuf[0] << 8) | rxbuf[1];
        return value;
    }

    SpiAdc::~SpiAdc() {
        if (m_spidev != nullptr) {
            free(m_spidev);
            m_spidev = nullptr;
        }
    }

}
