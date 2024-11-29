// A file that stores common definitions and types used by the MotorGo library.

#ifndef MOTORGO_TYPES_H
#define MOTORGO_TYPES_H

#include <Arduino.h>
#include <SPI.h>

namespace MotorGo
{

struct DCChannelParameters
{
  uint8_t in_1;
  uint8_t in_2;
  uint8_t enc_cs;
};

/**
 * @enum ControlMode
 * @brief Enumerates the control modes for motor operation.
 *
 * This enumeration defines various modes of operation for the motor, such as
 * voltage control, velocity control, torque control, position control, and
 * their respective open-loop variants.
 */
enum ControlMode
{
  None,
  Voltage,
  Velocity,
  Position,
  VelocityOpenLoop
};

/**
 * @struct PIDParameters
 * @brief Structure holding PID controller parameters.
 *
 * This structure encapsulates the proportional (P), integral (I), and
 * derivative (D) parameters used in PID control, along with additional
 * parameters such as output ramp rate, low pass filter time constant, and
 * limit for the output.
 */
struct PIDParameters
{
  float p;
  float i;
  float d;
  float output_ramp = 10000.0f;
  float lpf_time_constant = 0.1f;
  float limit = 10000.0f;
};

/**
 * @union packed_pid_parameters_t
 * @brief Union representing PID parameters in packed and raw byte formats.
 *
 * This union allows PIDParameters to be accessed either as a struct with
 * individual fields or as a raw byte array, facilitating easy storage or
 * transmission.
 */
typedef union
{
  struct __attribute__((packed))
  {
    float p;
    float i;
    float d;
    float output_ramp;
    float lpf_time_constant;
    float limit;
  };

  uint8_t raw[sizeof(PIDParameters)];
} packed_pid_parameters_t;

/**
 * @struct ChannelConfiguration
 * @brief Structure that stores the configuration for setting up a motor
 * channel. This includes the motor configuration, the power supply voltage,
 * and whether the motor should be reversed. If reversed is false, the motor
 * will rotate counter-clockwise with a positive command. If reversed is true,
 * the motor will rotate clockwise with a positive command.
 */
struct ChannelConfiguration
{
  float reversed;
};

/**
 * @var hspi
 * @brief Global instance of SPIClass for SPI communication.
 *
 * Used for SPI communication with peripherals.
 */
extern SPIClass hspi;
extern bool hspi_initialized;

/**
 * @brief Initializes the SPI interface for communication with the two
 *        encoders on the MotorGo Mini.
 */
void init_encoder_spi();

}  // namespace MotorGo

#endif  // MOTORGO_TYPES_H