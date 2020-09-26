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

#include <Servo.h>
#include "defineParams.h"

class Thruster
{
public:
    Thruster(uint8_t pwmPinNo);
    ~Thruster();
    void setRevCmd(float motorSpeed);
    void stop(void);
    void init(void);

private:
    uint32_t convMotorSpeedtoPwmSignal(float motorSpeed);
    uint8_t mypwmPinNo = 0;
    Servo myservo;
};

#endif // __THRUSTER_HPP__
