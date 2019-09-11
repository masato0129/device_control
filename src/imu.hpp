/**
 * @file imu.hpp
 * @author masato ogura
 * @brief 慣性航法センサクラス
 * @version 0.1
 * @date 2019-03-31
 * 
 * @copyright Copyright (c) 2019 masato ogura
 * 
 */

#include "quaternionFilters.h"
#include "MPU9250.h"
#include "defineParams.h"
#include "tagDefine.h"

#ifndef __IMU_HPP__
#define __IMU_HPP__

class Imu
{
public:
    Imu();
    ~Imu();
    void init();
    imuData_t update();
private:

    MPU9250* imu;
    void countup();
    linear_t getAccelData(MPU9250* imu);
    angular_t getGyroData(MPU9250* imu);
    linear_t getMagData(MPU9250* imu);
    float getTemplature(MPU9250* imu);

    imuData_t imuData = {
        0,//count
        0,//status 
        {0.0, 0.0, 0.0}, //acc
        {0.0, 0.0, 0.0}, //gyro
        {0.0, 0.0, 0.0}, //mag
        0.0 //temperature
    };
};

#endif // __IMU_HPP__
