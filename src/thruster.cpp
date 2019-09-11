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

#include <Arduino.h>
#include "thruster.hpp"

/**
 * @brief Construct a new Thruster:: Thruster object
 * 
 * @param plusPinNo 
 * @param minusPinNo 
 * @param pwmPinNo 
 * @param currentPinNo 
 */
Thruster::Thruster(uint8_t plusPinNo, uint8_t minusPinNo, uint8_t pwmPinNo, uint8_t currentPinNo)
{
    plus = plusPinNo;
    minus = minusPinNo;
    pwm = pwmPinNo;
    current = currentPinNo;

    pinMode(plus, OUTPUT);
    pinMode(minus, OUTPUT);
}

/**
 * @brief Destroy the Thruster:: Thruster object
 * 
 */
Thruster::~Thruster()
{
    //do nothing
}

/**
 * @brief モーター回転数を設定
 * 
 * @param motorSpeed 
 */
void Thruster::setRevCmd(int motorSpeed)
{
    int wk = abs(motorSpeed);

    if (wk > 256){
        stop();
        return;
    }

    if (motorSpeed > 0)
    {
        plusRev(wk);
    }else if(motorSpeed < 0){
        minusRev(wk);
    }else{
        stop();
    }
}


/**
 * @brief 正回転
 * 
 * @param motorSpeed 
 */
void Thruster::plusRev(int motorSpeed)
{
    digitalWrite(plus, HIGH);
    digitalWrite(minus, LOW);
    analogWrite(pwm, motorSpeed);
}

/**
 * @brief 逆回転
 * 
 * @param motorSpeed 
 */
void Thruster::minusRev(int motorSpeed)
{
    digitalWrite(plus, LOW);
    digitalWrite(minus, HIGH);
    analogWrite(pwm, motorSpeed);
}

/**
 * @brief 停止
 * 
 */
void Thruster::stop(void)
{
    digitalWrite(plus, LOW);
    digitalWrite(minus, LOW);
}

/**
 * @brief 推進機の電圧取得
 * 
 * @return float 電圧値
 */
float Thruster::getVoltageValue(void)
{
    int val = analogRead(current);
    return 5.0 * val / 1023.0; //10ビットADコンバータのため（2^10-1）
} 
