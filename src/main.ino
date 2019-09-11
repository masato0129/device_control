/**
 * @file main.ino
 * @author masato ogura
 * @brief arduino micro メイン分
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019 masato ogura
 * 
 */

#include <stdio.h>

#include "defineParams.h"
#include "thruster.hpp"
#include "imu.hpp"

/**
 * @brief オブジェクトの生成
 */
Thruster thruster1(MOTOR1_PLUS_PIN, MOTOR1_MINUS_PIN, MOTOR1_PWM_PIN, MOTOR1_CURRENT_PIN);
Thruster thruster2(MOTOR2_PLUS_PIN, MOTOR2_MINUS_PIN, MOTOR2_PWM_PIN, MOTOR2_CURRENT_PIN);
Thruster thruster3(MOTOR3_PLUS_PIN, MOTOR3_MINUS_PIN, MOTOR3_PWM_PIN, MOTOR3_CURRENT_PIN);
Thruster thruster4(MOTOR4_PLUS_PIN, MOTOR4_MINUS_PIN, MOTOR4_PWM_PIN, MOTOR4_CURRENT_PIN);
Imu imu;

/**
 * @brief 初期設定
 */
void setup(void)
{
  Serial.begin(BAUNDRATE);
  while(!Serial){};

  imu.init();
}


/**
 * @brief mainループ
 */
void loop(void)
{
  uint8_t recvBuf[128] = {0};
  uint8_t sendBuf[128] = {0};

  uint32_t recvCounter = 0;
  while(Serial.available() > 0)
  {
    uint8_t a = Serial.read();
    recvBuf[recvCounter] = a;
    recvCounter++;
  }

  // 受信データ
  recvData_t recvData;
  memcpy(&recvData, &recvBuf, (size_t)sizeof(recvData));

  thruster1.setRevCmd(recvData.thruster.th1);
  thruster2.setRevCmd(recvData.thruster.th2);
  thruster3.setRevCmd(recvData.thruster.th3);
  thruster4.setRevCmd(recvData.thruster.th4);

  // 送信データ
  sendData_t sendData;
  memcpy(&sendData, 0, (size_t)sizeof(sendData));

  sendData.imu = imu.update();
  sendData.thruster.th1 = thruster1.getVoltageValue();
  sendData.thruster.th2 = thruster2.getVoltageValue();
  sendData.thruster.th3 = thruster3.getVoltageValue();
  sendData.thruster.th4 = thruster4.getVoltageValue();

  memcpy(sendBuf, &sendData, (size_t)sizeof(sendData));
  Serial.write(sendBuf, (size_t)sizeof(sendBuf));
  delay(100);

}
