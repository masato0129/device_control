/**
 * @file thruster.hpp
 * @author masato ogura
 * @brief 推進機クラス
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019 masato ogura
 * 
 */

#ifndef __THRUSTER_HPP__
#define __THRUSTER_HPP__

#include <stdio.h>

class Thruster
{
public:
    Thruster(uint8_t plusPinNo, uint8_t minusPinNo, uint8_t pwmPinNo, uint8_t currentPinNo);
    ~Thruster();
    void setRevCmd(int motorSpeed);
    void plusRev(int motorSpeed);
    void minusRev(int motorSpeed);
    void stop(void);
    float getVoltageValue(void);

private:
    uint8_t plus;
    uint8_t minus;
    uint8_t pwm;
    uint8_t current;
};

#endif // __THRUSTER_HPP__

