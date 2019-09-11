/**
 * @file defineParams.h
 * @author masato ogura 
 * @brief パラメータ定義
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019 masato ogura
 * 
 */

#ifndef __DEFINEPARAMS_H__
#define __DEFINEPARAMS_H__

#include "Arduino.h"

// モーター1
const uint8_t MOTOR1_PLUS_PIN    = 1;
const uint8_t MOTOR1_MINUS_PIN   = 0;
const uint8_t MOTOR1_PWM_PIN     = 5;
const uint8_t MOTOR1_CURRENT_PIN = A3;

// モーター2
const uint8_t MOTOR2_PLUS_PIN    = 4;
const uint8_t MOTOR2_MINUS_PIN   = 7;
const uint8_t MOTOR2_PWM_PIN     = 6;
const uint8_t MOTOR2_CURRENT_PIN = A2;

// モーター3
const uint8_t MOTOR3_PLUS_PIN    = 8;
const uint8_t MOTOR3_MINUS_PIN   = 9;
const uint8_t MOTOR3_PWM_PIN     = 10;
const uint8_t MOTOR3_CURRENT_PIN = A1;

// モーター4
const uint8_t MOTOR4_PLUS_PIN    = 11;
const uint8_t MOTOR4_MINUS_PIN   = 12;
const uint8_t MOTOR4_PWM_PIN     = 13;
const uint8_t MOTOR4_CURRENT_PIN = A0;

// 深度センサ
const uint8_t DEPTH_PIN = A5;

// imu関係
#define I2Cclock 400000
#define I2Cport Wire
#define MPU9250_ADDRESS MPU9250_ADDRESS_AD0   // Use either this line or the next to select which I2C address your device is using
//#define MPU9250_ADDRESS MPU9250_ADDRESS_AD1
#define AHRS true         // Set to false for basic data read

// シリアル通信
#define BAUNDRATE 115200

// デバイスエラー
#define DVICE_ERORR 0xFF

// デバッグ関係
#define SerialDebug false  // Set to true to get Serial output for debugging

#endif // __DEFINEPARAMS_H__
