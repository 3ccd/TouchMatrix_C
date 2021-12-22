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

    int SpiAdc::read(unsigned char *p_rxbuffer, u_int8_t p_rxlen) const {
        /*struct spi_ioc_transfer message[1];
        memset(message, 0, sizeof(message));

        message[0].rx_buf = *p_rxbuffer;
        message[0].p_rxlen = p_rxlen;
        int ret = ioctl(fd, SPI_IOC_MESSAGE(1), message);*/
        int ret = ::read(fd, p_rxbuffer, p_rxlen);
        return ret;
    }

    SpiAdc::~SpiAdc() {
        if (m_spidev != nullptr) {
            free(m_spidev);
            m_spidev = nullptr;
        }
    }

}
