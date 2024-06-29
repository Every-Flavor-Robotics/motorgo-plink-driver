// A file that stores common definitions and types used by the MotorGo library.

#ifndef MOTORGO_TYPES_H
#define MOTORGO_TYPES_H

#include <Arduino.h>
#include <SPI.h>

// Pin definitions for the MotorGo Plink 0.1
#define P39 39
#define P40 40
#define P44 41
#define P47 42
#define P4 35
#define P7 36
#define P3 37
#define P9 43
#define P43 44
#define P38 21
#define P8 38
#define P41 47
#define P42 48

#define M1_PH 15
#define M1_EN 16

#define M2_PH 17
#define M2_EN 18

#define M3_PH 8
#define M3_EN 3

#define M4_PH 10
#define M4_EN 11

#define ENC_SDA 6
#define ENC_SCL 7
#define ENC_MOSI 45

#define M1_ENC_CS 5
#define M2_ENC_CS 4
#define M3_ENC_CS 9
#define M4_ENC_CS 12

// USB Power and IMU
#define HIDDEN_SDA 13
#define HIDDEN_SCL 14

// Qwiic
#define SDA 2
#define SCL 1

namespace MotorGo
{

struct DCChannelParameters
{
  uint8_t in_1;
  uint8_t in_2;
  uint8_t pwm_channel_1;
  uint8_t pwm_channel_2;
  uint8_t enc_cs;
};

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