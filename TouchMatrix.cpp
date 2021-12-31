//
// Created by g1853149 on 2021/12/21.
//

#include <cstring>
#include <cstdint>

#include "TouchMatrix.h"

namespace tm_control {

    TouchMatrix::TouchMatrix(SpiAdc &adc, Selector &sel, Led &drv) : adc(adc), sel(sel), drv(drv) {
        prevSensorNum = -1;
    }

    uint16_t TouchMatrix::getRawValue(uint16_t *data_ptr, int sensorNum, bool ir_enable) {
        sel.setMultiplex(sensorNum);
        setLed(sensorNum, ir_enable);

        unsigned char buffer[2];
        memset(buffer, 0, sizeof(buffer));

        int ret = adc.read(&buffer[0], sizeof(buffer));

        *data_ptr = (buffer[0] << 8) | buffer[1];
        return ret;
    }

    void TouchMatrix::getFrame(uint16_t *data_ptr, int data_len) {
        if(data_len < 0)return;
        for(int i = 0; i < data_len; i++){
            uint16_t irOn = 0;
            uint16_t irOff = 0;
            getRawValue(&irOn, i, true);
            getRawValue(&irOff, i, false);
            data_ptr[i] = irOn - irOff;
        }
    }

    void TouchMatrix::setLed(int sensorNum, bool enable) {
        if(prevSensorNum == sensorNum) return;
        if(!enable){
            drv.setEnable(false);
            return;
        }

        drv.clearBuffer();
        int row = int((sensorNum / 11) % 2);
        drv.set(sensorNum - 11, true);
        drv.set(sensorNum-row, true);
        drv.set(sensorNum+(1-row), true);
        drv.set(sensorNum + 11, true);
        drv.sendBuffer();
        drv.setEnable(true);
        prevSensorNum = sensorNum;
    }
}