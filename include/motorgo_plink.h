#ifndef MOTORGO_PLINK_H
#define MOTORGO_PLINK_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "motorgo_channel.h"
#include "motorgo_common.h"

namespace MotorGo
{

/**
 * @class MotorGoPlink
 * @brief Provides control and management for the MotorGo Plink hardware.
 *
 * This class sets up and encapsulates the MotorChannel objects for the four
 * motor channels on the MotorGo Plink. The MotorChannel is the primary
 * interface for controlling and managing BLDC motors using the MotorGo
 * hardware.
 */
class MotorGoPlink
{
 private:
  DCChannelParameters ch1_params = {
      .in_1 = M1_PH,
      .in_2 = M1_EN,
      .pwm_channel_1 = 0,
      .pwm_channel_2 = 1,
      .enc_cs = M1_ENC_CS,
  };

  DCChannelParameters ch2_params = {
      .in_1 = M2_PH,
      .in_2 = M2_EN,
      .pwm_channel_1 = 2,
      .pwm_channel_2 = 3,
      .enc_cs = M2_ENC_CS,
  };

  DCChannelParameters ch3_params = {
      .in_1 = M3_PH,
      .in_2 = M3_EN,
      .pwm_channel_1 = 4,
      .pwm_channel_2 = 5,
      .enc_cs = M3_ENC_CS,
  };

  DCChannelParameters ch4_params = {
      .in_1 = M4_PH,
      .in_2 = M4_EN,
      .pwm_channel_1 = 6,
      .pwm_channel_2 = 7,
      .enc_cs = M4_ENC_CS,
  };

  // Task handle for the FreeRTOS task
  TaskHandle_t encoderTaskHandle;

  // Static member function for the FreeRTOS task
  static void encoderUpdateTask(void *pvParameters);

 public:
  MotorGoPlink();

  void init();
  void stop();  // Method to stop the FreeRTOS task

  // Define the four motor channels on the MotorGo Plink
  MotorChannel ch1;
  MotorChannel ch2;
  MotorChannel ch3;
  MotorChannel ch4;
};

}  // namespace MotorGo

#endif  // MOTORGO_PLINK_H
