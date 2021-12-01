//
// Created by UraChihiro on 2021/11/30.
//

#ifndef TOUCHMATRIX_SELECTOR_H
#define TOUCHMATRIX_SELECTOR_H

#include "Singleton.h"

namespace tm_control{

    struct Decorder{
        int a, b, c, enable;
    };

    struct Multiplexer{
        int a, b, c, d;
    };

    struct LedDriver{
        int sin, clk, rlk, enable;
    };

    class Selector : public Singleton<Selector>{
    private:
        const Decorder DC;
        const Multiplexer MUX;
        const LedDriver DRV;

        void muxSetValue(int value);
        void decSetValue(int value);

    public:
        friend class Singleton<Selector>;

    protected:
        Selector(Decorder dec, Multiplexer mux, LedDriver drv);
        virtual ~Selector();
    };

}

#endif //TOUCHMATRIX_SELECTOR_H
