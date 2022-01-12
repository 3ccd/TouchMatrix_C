//
// Created by user on 2021/12/01.
//

#ifndef TOUCHMATRIX_LED_H
#define TOUCHMATRIX_LED_H

#include "Singleton.h"

namespace tm_control{

    struct Driver{
        int sin, clk, rck, l_enable;
    };

    class Led{
    private:
        const Driver DRV;
        static constexpr int DRV_CNT = 8;
        static constexpr int DRV_CH = 16;
        unsigned char buffer[100]{};

        int bufferLength();
        void initBuffer();

        static void shift(int pin);

    public:
        explicit Led(Driver& drv);
        void sendBuffer();
        void set(int num, bool output);
        void setEnable(bool led_enable) const;
        void clearBuffer();
        ~Led();

    };

}

#endif //TOUCHMATRIX_LED_H
