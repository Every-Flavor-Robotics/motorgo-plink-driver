#include "motorgo_channel.h"

// MotorChannel class constructor
MotorGo::MotorChannel::MotorChannel(DCChannelParameters params,
                                    const char* name)
    : name(name),
      in_1(params.in_1),
      in_2(params.in_2),
      pwm_channel_1(params.pwm_channel_1),
      pwm_channel_2(params.pwm_channel_2),
      encoder(MagneticSensorMT6701SSI(params.enc_cs))
{
}

void MotorGo::MotorChannel::init()
{
  // Init encoder
  encoder.init(&MotorGo::hspi);

  Serial.println("Initializing Motor Channel");

  // Setup PWM
  ledcSetup(pwm_channel_1, 20000, 8);
  ledcSetup(pwm_channel_2, 20000, 8);

  // Attach PWM channels
  ledcAttachPin(in_1, pwm_channel_1);
  ledcAttachPin(in_2, pwm_channel_2);
}

void MotorGo::MotorChannel::loop()
{
  // Update the PID controlller state
  encoder.update();
}

// Getters
float MotorGo::MotorChannel::get_position() { return encoder.getAngle(); }
float MotorGo::MotorChannel::get_velocity() { return encoder.getVelocity(); }
float MotorGo::MotorChannel::get_power() { return target_power; }

// Setters

void MotorGo::MotorChannel::set_power(float target)
{
  // Constrain the target power to the range [-1, 1]
  target_power = _constrain(target, -1.0f, 1.0f);

  //   Update PWM parameters
  if (target_power > 0)
  {
    ledcWrite(pwm_channel_1, int(255 * target_power));
    ledcWrite(pwm_channel_2, 0);
  }
  else if (target_power < 0)
  {
    ledcWrite(pwm_channel_1, 0);
    ledcWrite(pwm_channel_2, int(255 * -target_power));
  }
  else
  {
    if (brake)
    {
      ledcWrite(pwm_channel_1, 255);
      ledcWrite(pwm_channel_2, 255);
    }
    else
    {
      ledcWrite(pwm_channel_1, 0);
      ledcWrite(pwm_channel_2, 0);
    }
  }
}

void MotorGo::MotorChannel::set_brake() { brake = true; }

void MotorGo::MotorChannel::set_coast() { brake = false; }

void MotorGo::MotorChannel::zero_position()
{
  // Shaft angle returns the filtered angle, with the sensor offset applied
  //   Add current sensor_offset back to the current shaft angle to
  //   recover the filtered (but not offset) angle
  sensor_offset = encoder.getAngle() + sensor_offset;
}
