/**
 * @file thruster.cpp
 * @author masato ogura
 * @brief 推進機クラス
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019 masato ogura
 * 
 */

#include "thruster.hpp"

/**
 * @brief Construct a new Thruster:: Thruster object
 * 
 * @param pwmPinNo 
 */
Thruster::Thruster(uint8_t pwmPinNo)
{
  mypwmPinNo = pwmPinNo;
}

/**
 * @brief Destroy the Thruster:: Thruster object
 * 
 */
Thruster::~Thruster()
{
  // do nothing
}

/**
 * @brief pwm
 * 
 */
void Thruster::init(void)
{
    myservo.attach(mypwmPinNo);
}

/**
 * @brief モーター回転数を設定
 * 
 * @param motorSpeed 
 */
void Thruster::setRevCmd(float motorSpeed)
{
    if (motorSpeed > 1){
        motorSpeed = 1;
    }
    if (motorSpeed < -1){
        motorSpeed = -1;
    }
    int pwmSignal = convMotorSpeedtoPwmSignal(motorSpeed);
    //Serial.println(pwmSignal);
    myservo.writeMicroseconds(pwmSignal);
}

/**
 * @brief モーター回転数からpwm周期に変換
 * 
 * @param motorSpeed
 * 
 * @return uint32_t
 */
uint32_t  Thruster::convMotorSpeedtoPwmSignal(float motorSpeed)
{
    return int(motorSpeed * 100 * 4 + 1500);
}

/**
 * @brief 停止
 * 
 */
void Thruster::stop(void)
{
	myservo.writeMicroseconds(MOTOR_SIGNAL_STOP); // send "stop" signal to ESC.
}
