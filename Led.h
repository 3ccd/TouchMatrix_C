//
// Created by user on 2021/12/01.
//

#ifndef TOUCHMATRIX_LED_H
#define TOUCHMATRIX_LED_H

#include "Singleton.h"

namespace tm_control{

    struct Driver{
        int sin, sck, rck, enable;
    };

    class Led: public Singleton<Led>{
    private:
        const Driver DRV;

    public:
        friend class Singleton<Led>;

    };

}

#endif //TOUCHMATRIX_LED_H
