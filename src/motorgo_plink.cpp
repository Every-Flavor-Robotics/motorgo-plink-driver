#include "motorgo_plink.h"

MotorGo::MotorGoPlink::MotorGoPlink()
    : ch1(ch1_params, "ch1"),
      ch2(ch2_params, "ch2"),
      ch3(ch3_params, "ch3"),
      ch4(ch4_params, "ch4")
{
  // Init spi bus
  MotorGo::init_encoder_spi();

  delay(10);

  // Create the encoder update task
  xTaskCreate(MotorGoPlink::encoderUpdateTask,  // Task function
              "EncoderUpdateTask",  // Name of the task (for debugging)
              2048,                 // Stack size (in words)
              this,                 // Task input parameter
              1,                    // Priority of the task
              &encoderTaskHandle    // Task handle
  );
}

void MotorGo::MotorGoPlink::encoderUpdateTask(void *pvParameters)
{
  MotorGoPlink *instance = static_cast<MotorGoPlink *>(pvParameters);
  while (true)
  {
    instance->ch1.loop();
    instance->ch2.loop();
    instance->ch3.loop();
    instance->ch4.loop();
    vTaskDelay(pdMS_TO_TICKS(2));
  }
}

// Optional: a method to stop the task if necessary
void MotorGo::MotorGoPlink::stop()
{
  if (encoderTaskHandle != nullptr)
  {
    vTaskDelete(encoderTaskHandle);
    encoderTaskHandle = nullptr;
  }
}