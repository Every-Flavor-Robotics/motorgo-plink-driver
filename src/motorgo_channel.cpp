#include "motorgo_channel.h"

// MotorChannel class constructor
MotorGo::MotorChannel::MotorChannel(DCChannelParameters params,
                                    const char* name)
    : name(name),
      in_1(params.in_1),
      in_2(params.in_2),
      motor(DCMotor()),
      driver(DCDriver2PWM(in_1, in_2)),
      encoder(MagneticSensorMT6701SSI(params.enc_cs))
{
}

void MotorGo::MotorChannel::init()
{
  driver.voltage_power_supply = 5.0;
  driver.voltage_limit = 17;
  driver.pwm_frequency = 20000;
  driver.init();

  // Init encoder
  encoder.init(&MotorGo::hspi);

  motor.linkDriver(&driver);
  motor.linkSensor(&encoder);
  motor.voltage_limit = 5.0;
  motor.controller = MotionControlType::torque;
  motor.torque_controller = TorqueControlType::voltage;
  motor.init();

  Serial.println("Initializing Motor Channel");
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

  motor.move(target_power);
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
