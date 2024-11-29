// Header file for the Motor Channel class.

#ifndef MOTOR_CHANNEL_H
#define MOTOR_CHANNEL_H

#include <SPI.h>
#include <SimpleFOC.h>
#include <Wire.h>

#include "SimpleDCMotor.h"
#include "encoders/calibrated/CalibratedSensor.h"
#include "encoders/mt6701/MagneticSensorMT6701SSI.h"
#include "motorgo_common.h"

namespace MotorGo
{

/**
 * @class MotorChannel
 * @brief Provides control and management for each of the MotorGo DC motor
 * channels.
 *
 * This class encapsulates the functionality for controlling and managing
 * DC motors using the MotorGo hardware. It provides functions for setting
 * up motors and encoders, running control loops, and setting control modes.
 */
class MotorChannel
{
 public:
  /**
   * @brief Constructor for the MotorChannel class.
   * @param params DCChannelParameters structure containing the pin
   * configuration for the motor channel.
   * @param name The name of the motor channel, used for saving calibration
   * parameters to EEPROM.
   */
  MotorChannel(DCChannelParameters params, const char* name);
  MotorChannel(const MotorChannel&) = delete;  // Delete copy constructor
  MotorChannel& operator=(const MotorChannel&) =
      delete;  // Delete copy assignment operator

  void init();

  /**
   * @brief Runs the control loop for the motor channel and updates encoder
   *        data. This should be run as fast as possible, without delays.
   */
  void loop();

  /**
   * @brief Set the power of the motor. This function will set
   * the percentage of the maximum power the motor should run at. The value
   * should be between -1.0 and 1.0, where -1.0 is full reverse and 1.0 is full.
   */
  void set_power(float target);

  void set_brake();
  void set_coast();

  /**
   * @brief Sets the current position of the motor to zero.
   *        This function resets the motor's position value to zero.
   */
  void zero_position();

  /**
   * @brief Retrieves the current velocity of the motor.
   * @return The motor's velocity in rad/s.
   */
  float get_velocity();

  /**
   * @brief Retrieves the current position of the motor.
   * @return The motor's position in radians.
   */
  float get_position();

  /**
   * @brief Retrieves the current voltage of the motor.
   * @return The motor's voltage in V.
   */
  float get_power();

 private:
  //    Motor name
  //   Used to store calibration parameters in EEPROM
  const char* name;

  const int in_1;
  const int in_2;

  DCMotor motor;
  DCDriver2PWM driver;

  MagneticSensorMT6701SSI encoder;

  // Percentage of the maximum power the motor should run at
  float target_power = 0.0;

  bool brake = false;

  float sensor_offset = 0.0;
};

}  // namespace MotorGo

#endif  // MOTOR_CHANNEL_H