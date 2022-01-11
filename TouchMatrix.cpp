//
// Created by g1853149 on 2021/12/21.
//

#include <cstring>
#include <cstdint>

#include <wiringPi.h>

#include "TouchMatrix.h"

namespace tm_control {

    TouchMatrix::TouchMatrix(SpiAdc &adc, Selector &sel, Led &drv) : adc(adc), sel(sel), drv(drv) {
        prevSensorNum = -1;
    }

    uint16_t TouchMatrix::getRawValue(int sensorNum, bool ir_enable) {
        setLed(sensorNum, ir_enable);
        sel.setMultiplex(sensorNum);

        delayMicroseconds(50);

        adc.read();
        uint16_t value = adc.read();

        return value;
    }

    void TouchMatrix::getFrame(uint16_t *data_ptr, int data_len) {
        if(data_len < 0)return;
        for(int i = 0; i < data_len; i++){
            uint16_t irOn = 0;
            uint16_t irOff = 0;
            irOn = getRawValue(i, true);
            //irOff = getRawValue(i, false);
            int tmp = (int)irOn - (int)irOff;
            if(tmp < 0) tmp = 0;
            data_ptr[i] = (uint16_t)tmp;
        }
    }

    void TouchMatrix::setLed(int sensorNum, bool enable) {
        //if(prevSensorNum == sensorNum) return;
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