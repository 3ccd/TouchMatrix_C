//
// Created by UraChihiro on 2021/11/30.
//

#ifndef TOUCHMATRIX_SELECTOR_H
#define TOUCHMATRIX_SELECTOR_H

#include "Singleton.h"

namespace tm_control{

    struct Decoder{
        int a, b, c, enable;
    };

    struct Multiplexer{
        int a, b, c, d;
    };

    class Selector{
    private:
        const Decoder DC;
        const Multiplexer MUX;

        void muxInit() const;
        void decInit() const;
        void muxSetValue(int value) const;
        void decSetValue(int value) const;

    public:
        Selector(Decoder& dec, Multiplexer& mux);
        void setMultiplex(int value);
        ~Selector();
    };

}

#endif //TOUCHMATRIX_SELECTOR_H
