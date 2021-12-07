//
// Created by user on 2021/12/01.
//

#ifndef TOUCHMATRIX_LED_H
#define TOUCHMATRIX_LED_H

#include "Singleton.h"

namespace tm_control{

    struct Driver{
        int sin, clk, rck, enable;
    };

    class Led: public Singleton<Led>{
    private:
        const Driver DRV;
        static constexpr int DRV_CNT = 8;
        static constexpr int DRV_CH = 16;
        unsigned char buffer[100]{};

        int bufferLength();
        void initBuffer();

        static void shift(int pin);
        void sendBuffer();
        void set(int num, bool output);

    public:
        friend class Singleton<Led>;

    protected:
        explicit Led(Driver& drv);
        ~Led() override;

    };

}

#endif //TOUCHMATRIX_LED_H
