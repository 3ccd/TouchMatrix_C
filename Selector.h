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

        void muxInit() const;
        void decInit() const;
        void muxSetValue(int value) const;
        void decSetValue(int value) const;

    public:
        friend class Singleton<Selector>;
        void setMultiplex(int value);

    protected:
        Selector(Decorder dec, Multiplexer mux);
        ~Selector() override;
    };

}

#endif //TOUCHMATRIX_SELECTOR_H
