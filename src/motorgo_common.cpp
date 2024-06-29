#include "motorgo_common.h"

#include "SimpleFOC.h"

// Encoder I2C bus, define and initialize here to avoid multiple definitions
SPIClass MotorGo::hspi(HSPI);
bool MotorGo::hspi_initialized = false;

void MotorGo::init_encoder_spi()
{
  //   Guard to prevent multiple initializations, which could cause a crash
  if (!hspi_initialized)
  {
    Serial.println("Initializing SPI for encoders");
    hspi_initialized = true;
    hspi.begin(ENC_SCL, ENC_SDA, ENC_MOSI);
  }
}
