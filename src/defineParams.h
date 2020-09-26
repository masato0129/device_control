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

// 推進機
#define MOTOR_RIGHT_FRONT_PWM_PIN  (5)
#define MOTOR_RIGHT_CENTER_PWM_PIN (6)
#define MOTOR_RIGHT_REAR_PWM_PIN   (9)
#define MOTOR_LEFT_FRONT_PWM_PIN   (10)
#define MOTOR_LEFT_CENTER_PWM_PIN  (11)
#define MOTOR_LEFT_REAR_PWM_PIN    (13)

// pwm信号の上下限
#define MOTOR_SIGNAL_STOP (1500)
#define MOTOR_SIGNAL_MAX  (1900) 
#define MOTOR_SIGNAL_MIN  (1100) 

// シリアル通信
#define BAUNDRATE 115200

// デバイスエラー
#define DVICE_ERORR 0xFF

// デバッグ関係
#define SerialDebug false

#endif // __DEFINEPARAMS_H__
