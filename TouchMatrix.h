//
// Created by g1853149 on 2021/12/21.
//

#ifndef TOUCHMATRIX_TOUCHMATRIX_H
#define TOUCHMATRIX_TOUCHMATRIX_H

#include "SpiAdc.h"
#include "Selector.h"
#include "Led.h"

namespace tm_control{
    class TouchMatrix {
    private:
        SpiAdc& adc;
        Selector& sel;
        Led& drv;

        int prevSensorNum;


    public:
        TouchMatrix(SpiAdc &adc, Selector &sel, Led &drv);
        u_int16_t getRawValue(int sensorNum, bool ir_enable);
        void getFrame(uint16_t *data_ptr, int data_len);
        void setLed(int sensorNum, bool enable);

    };
}



#endif //TOUCHMATRIX_TOUCHMATRIX_H
