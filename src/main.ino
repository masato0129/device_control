#define USE_USBCON // for atmega32u4

#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <thruster.hpp>

/**
 * @brief create device object
 */
Thruster thruster1(MOTOR_RIGHT_FRONT_PWM_PIN );
Thruster thruster2(MOTOR_RIGHT_CENTER_PWM_PIN);
Thruster thruster3(MOTOR_RIGHT_REAR_PWM_PIN  );
Thruster thruster4(MOTOR_LEFT_FRONT_PWM_PIN  );
Thruster thruster5(MOTOR_LEFT_CENTER_PWM_PIN );
Thruster thruster6(MOTOR_LEFT_REAR_PWM_PIN   );

/**
 * @brief ros setting
 */
ros::NodeHandle  nh;
std_msgs::Float32MultiArray array;

void callback(const std_msgs::Float32MultiArray& array)
{
  thruster1.setRevCmd(array.data[0]);
  thruster2.setRevCmd(array.data[1]);
  thruster3.setRevCmd(array.data[2]);
  thruster4.setRevCmd(array.data[3]);
  thruster5.setRevCmd(array.data[4]);
  thruster6.setRevCmd(array.data[5]);
}

ros::Subscriber <std_msgs::Float32MultiArray> sub("array", callback);

/**
 * @brief 定周期変数
 */
unsigned long prev, interval;

void setup()
{
  array.data_length = 6;
  array.data = (float *)malloc(sizeof(float)*6);
  array.data[0] = 0;
  array.data[1] = 0;
  array.data[2] = 0;
  array.data[3] = 0;
  array.data[4] = 0;
  array.data[5] = 0;

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);

  thruster1.init();
  thruster2.init();
  thruster3.init();
  thruster4.init();
  thruster5.init();
  thruster6.init();
}

void loop()
{
  nh.spinOnce();
}
