/**
 * @file tagDefine.h
 * @author masato ogura
 * @brief 構造体関係定義
 * @version 0.1
 * @date 2019-04-07
 * 
 * @copyright Copyright (c) 2019 masato ogura
 * 
 */

/**
 * @brief 並進運動
 */
typedef struct linear_t{
    float x;
    float y;
    float z;
}linear_t;

/**
 * @brief 回転運動
 */
typedef struct angular_t{
    float roll;
    float pitch;
    float yaw;
}angular_t;

/**
 * @brief imuデータ
 */
typedef struct imuData{
    uint32_t count;
    uint32_t status;
    linear_t acc;
    angular_t gyro;
    linear_t mag;
    float temperature;
}imuData_t;

/**
 * @brief 推進機指令
 */
typedef struct thrusterCommandData{
    int32_t th1;
    int32_t th2;
    int32_t th3;
    int32_t th4;
}thrusterCommandData_t;

/**
 * @brief 推進機電圧データ
 */
typedef struct thrusterValtageData{
    float th1;
    float th2;
    float th3;
    float th4;
}thrusterValtageData_t;

/**
 * @brief arduinoの送信データ
 */
typedef struct sendData{
    imuData_t imu;
    thrusterValtageData_t thruster; 
}sendData_t;

/**
 * @brief arduinoの受信データ
 */
typedef struct recvData{
    uint32_t count;
    thrusterCommandData_t thruster;
    uint8_t spr[123];
}recvData_t;
