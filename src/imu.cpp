/**
 * @file imu.cpp
 * @author masato ogura
 * @brief 慣性航法装置クラス
 * @version 0.1
 * @date 2019-04-06
 * 
 * @copyright Copyright (c) 2019 masato ogura
 * 
 */

#include "imu.hpp"

/**
 * @brief Construct a new Imu:: Imu object
 * 
 */
Imu::Imu(){
    imu = new MPU9250(MPU9250_ADDRESS, I2Cport, I2Cclock);
}

/**
 * @brief Destroy the Imu:: Imu object
 * 
 */
Imu::~Imu(){
    // do nothing
    delete imu;
}

/**
 * @brief カウントアップ
 * 
 */
void Imu::countup()
{
    if(imuData.count >= 0xFFFFFFFF)
    {
        imuData.count = 0;
    }
    imuData.count++;
}

/**
 * @brief 温度データ取得
 * 
 * @param imu 
 * @return float 
 */
float Imu::getTemplature(MPU9250* imu)
{
    int templatureCount = imu->readTempData();
    return ((float) templatureCount) / 333.87 + 21.0;
}

/**
 * @brief 加速度データ取得
 * 
 * @param imu 
 * @return linear_t 
 */
linear_t Imu::getAccelData(MPU9250* imu)
{
    linear_t xyz = {0.0, 0.0, 0.0};

    imu->readAccelData(imu->accelCount);  // Read the x/y/z adc values

    // Now we'll calculate the accleration value into actual g's
    // This depends on scale being set
    imu->ax = (float)imu->accelCount[0] * imu->aRes; // - imu->accelBias[0];
    imu->ay = (float)imu->accelCount[1] * imu->aRes; // - imu->accelBias[1];
    imu->az = (float)imu->accelCount[2] * imu->aRes; // - imu->accelBias[2];

    xyz.x = imu->ax; 
    xyz.y = imu->ay; 
    xyz.z = imu->az; 
    
    return xyz;
}

/**
 * @brief 角速度取得
 * 
 * @param imu 
 * @return angular_t 
 */
angular_t Imu::getGyroData(MPU9250* imu)
{
    angular_t ang = {0.0, 0.0, 0.0};

    imu->readGyroData(imu->gyroCount);  // Read the x/y/z adc values

    // Calculate the gyro value into actual degrees per second
    // This depends on scale being set
    imu->gx = (float)imu->gyroCount[0] * imu->gRes;
    imu->gy = (float)imu->gyroCount[1] * imu->gRes;
    imu->gz = (float)imu->gyroCount[2] * imu->gRes;

    ang.roll  = imu->gx;
    ang.pitch = imu->gy;
    ang.yaw   = imu->gz;

    return ang;
}

/**
 * @brief 地磁気取得
 * 
 * @param imu 
 * @return angular_t 
 */
linear_t Imu::getMagData(MPU9250* imu)
{
    linear_t mag = {0.0, 0.0, 0.0};

    imu->readMagData(imu->magCount);  // Read the x/y/z adc values

    // Calculate the magnetometer values in milliGauss
    // Include factory calibration per data sheet and user environmental
    // corrections
    // Get actual magnetometer value, this depends on scale being set
    imu->mx = (float)imu->magCount[0] * imu->mRes
                * imu->factoryMagCalibration[0] - imu->magBias[0];
    imu->my = (float)imu->magCount[1] * imu->mRes
                * imu->factoryMagCalibration[1] - imu->magBias[1];
    imu->mz = (float)imu->magCount[2] * imu->mRes
                * imu->factoryMagCalibration[2] - imu->magBias[2];

    mag.x = imu->mx;
    mag.y = imu->my;
    mag.z = imu->mz;

    return mag;
}

/**
 * @brief 初期化
 * 
 */
void Imu::init()
{
    byte c = imu->readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);

    if (SerialDebug)
    {
        Serial.print(F("MPU9250 I AM 0x"));
        Serial.print(c, HEX);
        Serial.print(F(" I should be 0x"));
        Serial.println(0x71, HEX);
    }

    if (c == 0x71) // WHO_AM_I should always be 0x71
    {
        if (SerialDebug)
        {
            Serial.println(F("MPU9250 is online..."));
        }

        // Start by performing self test and reporting values
        imu->MPU9250SelfTest(imu->selfTest);
        if (SerialDebug)
        {
            Serial.println(F("MPU9250 is online..."));
            Serial.print(F("x-axis self test: acceleration trim within : "));
            Serial.print(imu->selfTest[0],1); Serial.println("% of factory value");
            Serial.print(F("y-axis self test: acceleration trim within : "));
            Serial.print(imu->selfTest[1],1); Serial.println("% of factory value");
            Serial.print(F("z-axis self test: acceleration trim within : "));
            Serial.print(imu->selfTest[2],1); Serial.println("% of factory value");
            Serial.print(F("x-axis self test: gyration trim within : "));
            Serial.print(imu->selfTest[3],1); Serial.println("% of factory value");
            Serial.print(F("y-axis self test: gyration trim within : "));
            Serial.print(imu->selfTest[4],1); Serial.println("% of factory value");
            Serial.print(F("z-axis self test: gyration trim within : "));
            Serial.print(imu->selfTest[5],1); Serial.println("% of factory value");
        }

        // Calibrate gyro and accelerometers, load biases in bias registers
        imu->calibrateMPU9250(imu->gyroBias, imu->accelBias);
        imu->initMPU9250();
        // Initialize device for active mode read of acclerometer, gyroscope, and
        // temperature

        if (SerialDebug)
        {
            Serial.println("MPU9250 initialized for active data mode....");
        }

        // Read the WHO_AM_I register of the magnetometer, this is a good test of
        // communication
        byte d = imu->readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);

        if (SerialDebug)
        {
            Serial.print("AK8963 ");
            Serial.print("I AM 0x");
            Serial.print(d, HEX);
            Serial.print(" I should be 0x");
            Serial.println(0x48, HEX);
        }

        if (d != 0x48)
        {
            // Communication failed, stop here
            Serial.println(F("Communication failed, abort!"));
            Serial.flush();
            abort();
        }

        // Get magnetometer calibration from AK8963 ROM
        imu->initAK8963(imu->factoryMagCalibration);

        if (SerialDebug)
        {
            // Initialize device for active mode read of magnetometer
            Serial.println("AK8963 initialized for active data mode....");
        }

        if (SerialDebug)
        {
        //  Serial.println("Calibration values: ");
            Serial.print("X-Axis factory sensitivity adjustment value ");
            Serial.println(imu->factoryMagCalibration[0], 2);
            Serial.print("Y-Axis factory sensitivity adjustment value ");
            Serial.println(imu->factoryMagCalibration[1], 2);
            Serial.print("Z-Axis factory sensitivity adjustment value ");
            Serial.println(imu->factoryMagCalibration[2], 2);
        }
        // Get sensor resolutions, only need to do this once
        imu->getAres();
        imu->getGres();
        imu->getMres();

        if (SerialDebug)
        {
            // The next call delays for 4 seconds, and then records about 15 seconds of
            // data to calculate bias and scale.
            // imu->magCalMPU9250(imu->magBias, imu->magScale);
            Serial.println("AK8963 mag biases (mG)");
            Serial.println(imu->magBias[0]);
            Serial.println(imu->magBias[1]);
            Serial.println(imu->magBias[2]);

            Serial.println("AK8963 mag scale (mG)");
            Serial.println(imu->magScale[0]);
            Serial.println(imu->magScale[1]);
            Serial.println(imu->magScale[2]);
        }
    //    delay(2000); // Add delay to see results before serial spew of data
        if(SerialDebug)
        {
            Serial.println("Magnetometer:");
            Serial.print("X-Axis sensitivity adjustment value ");
            Serial.println(imu->factoryMagCalibration[0], 2);
            Serial.print("Y-Axis sensitivity adjustment value ");
            Serial.println(imu->factoryMagCalibration[1], 2);
            Serial.print("Z-Axis sensitivity adjustment value ");
            Serial.println(imu->factoryMagCalibration[2], 2);
        }
    } // if (c == 0x71)
    else
    {
        if (SerialDebug)
        {
            Serial.print("Could not connect to MPU9250: 0x");
            Serial.println(c, HEX);
            // Communication failed, stop here
            Serial.println(F("Communication failed, abort!"));
        }

        imuData.status = DVICE_ERORR;
        Serial.flush();
        abort();
    }
}

/**
 * @brief センサデータ更新
 * 
 */
imuData_t Imu::update()
{
    countup();
    // If intPin goes high, all data registers have new data
    // On interrupt, check if data ready interrupt
    if (imu->readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
    {
        imuData.acc  = getAccelData(imu);
        imuData.gyro = getGyroData(imu);
        imuData.mag  = getMagData(imu);
        imuData.temperature = getTemplature(imu);

    } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)

    // Must be called before updating quaternions!
    imu->updateTime();

    // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of
    // the magnetometer; the magnetometer z-axis (+ down) is opposite to z-axis
    // (+ up) of accelerometer and gyro! We have to make some allowance for this
    // orientationmismatch in feeding the output to the quaternion filter. For the
    // MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward
    // along the x-axis just like in the LSM9DS0 sensor. This rotation can be
    // modified to allow any convenient orientation convention. This is ok by
    // aircraft orientation standards! Pass gyro rate as rad/s
    MahonyQuaternionUpdate(imu->ax, imu->ay, imu->az, imu->gx * DEG_TO_RAD,
                            imu->gy * DEG_TO_RAD, imu->gz * DEG_TO_RAD, imu->my,
                            imu->mx, imu->mz, imu->deltat);

    if (!AHRS)
    {
        imu->delt_t = millis() - imu->count;
        if (imu->delt_t > 500)
        {
            if(SerialDebug)
            {
                // Print acceleration values in milligs!
                Serial.print("My X-acceleration: "); Serial.print(1000 * imuData.acc.x);
                Serial.print(" mg ");
                Serial.print("My Y-acceleration: "); Serial.print(1000 * imuData.acc.y);
                Serial.print(" mg ");
                Serial.print("My Z-acceleration: "); Serial.print(1000 * imuData.acc.z);
                Serial.println(" mg ");

                // Print gyro values in degree/sec
                Serial.print("X-gyro rate: "); Serial.print(imuData.gyro.roll, 3);
                Serial.print(" degrees/sec ");
                Serial.print("Y-gyro rate: "); Serial.print(imuData.gyro.pitch, 3);
                Serial.print(" degrees/sec ");
                Serial.print("Z-gyro rate: "); Serial.print(imuData.gyro.yaw, 3);
                Serial.println(" degrees/sec");

                // Print mag values in degree/sec
                Serial.print("X-mag field: "); Serial.print(imuData.mag.x);
                Serial.print(" mG ");
                Serial.print("Y-mag field: "); Serial.print(imuData.mag.y);
                Serial.print(" mG ");
                Serial.print("Z-mag field: "); Serial.print(imuData.mag.z);
                Serial.println(" mG");

                // Print temperature in degrees Centigrade
                Serial.print("Temperature is ");  Serial.print(imu->temperature, 1);
                Serial.println(" degrees C");
            }
            imu->count = millis();
            // digitalWrite(myLed, !digitalRead(myLed));  // toggle led
        } // if (imu->delt_t > 500)
    } // if (!AHRS)
    else
    {
        // Serial print and/or display at 0.5 s rate independent of data rates
        imu->delt_t = millis() - imu->count;

        // update LCD once per half-second independent of read rate
        if (imu->delt_t > 500)
        {
            if(SerialDebug)
            {
                Serial.print("ax = ");  Serial.print((int)1000 * imu->ax);
                Serial.print(" ay = "); Serial.print((int)1000 * imu->ay);
                Serial.print(" az = "); Serial.print((int)1000 * imu->az);
                Serial.println(" mg");

                Serial.print("gx = ");  Serial.print(imu->gx, 2);
                Serial.print(" gy = "); Serial.print(imu->gy, 2);
                Serial.print(" gz = "); Serial.print(imu->gz, 2);
                Serial.println(" deg/s");

                Serial.print("mx = ");  Serial.print((int)imu->mx);
                Serial.print(" my = "); Serial.print((int)imu->my);
                Serial.print(" mz = "); Serial.print((int)imu->mz);
                Serial.println(" mG");

                Serial.print("q0 = ");  Serial.print(*getQ());
                Serial.print(" qx = "); Serial.print(*(getQ() + 1));
                Serial.print(" qy = "); Serial.print(*(getQ() + 2));
                Serial.print(" qz = "); Serial.println(*(getQ() + 3));
            }

            // Define output variables from updated quaternion---these are Tait-Bryan
            // angles, commonly used in aircraft orientation. In this coordinate system,
            // the positive z-axis is down toward Earth. Yaw is the angle between Sensor
            // x-axis and Earth magnetic North (or true North if corrected for local
            // declination, looking down on the sensor positive yaw is counterclockwise.
            // Pitch is angle between sensor x-axis and Earth ground plane, toward the
            // Earth is positive, up toward the sky is negative. Roll is angle between
            // sensor y-axis and Earth ground plane, y-axis up is positive roll. These
            // arise from the definition of the homogeneous rotation matrix constructed
            // from quaternions. Tait-Bryan angles as well as Euler angles are
            // non-commutative; that is, the get the correct orientation the rotations
            // must be applied in the correct order which for this configuration is yaw,
            // pitch, and then roll.
            // For more see
            // http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
            // which has additional links.
            imu->yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ()
                            * *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1)
                            * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) - *(getQ()+3)
                            * *(getQ()+3));
            imu->pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ()
                            * *(getQ()+2)));
            imu->roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2)
                            * *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1)
                            * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) + *(getQ()+3)
                            * *(getQ()+3));
            imu->pitch *= RAD_TO_DEG;
            imu->yaw   *= RAD_TO_DEG;

            // Declination of SparkFun Electronics (40°05'26.6"N 105°11'05.9"W) is
            //    8° 30' E  ± 0° 21' (or 8.5°) on 2016-07-19
            // - http://www.ngdc.noaa.gov/geomag-web/#declination
            imu->yaw  -= 8.5;
            imu->roll *= RAD_TO_DEG;

            if(SerialDebug)
            {
                Serial.print("Yaw, Pitch, Roll: ");
                Serial.print(imu->yaw, 2);
                Serial.print(", ");
                Serial.print(imu->pitch, 2);
                Serial.print(", ");
                Serial.println(imu->roll, 2);

                Serial.print("rate = ");
                Serial.print((float)imu->sumCount / imu->sum, 2);
                Serial.println(" Hz");
            }

            imu->count = millis();
            imu->sumCount = 0;
            imu->sum = 0;
        } // if (imu->delt_t > 500)
    } // if (AHRS)
    return imuData;
}