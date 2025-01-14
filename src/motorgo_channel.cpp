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

void MotorGo::MotorChannel::init(ChannelConfiguration channel_config)
{
  driver.voltage_power_supply = channel_config.power_supply_voltage;
  driver.voltage_limit = 15.0;
  driver.pwm_frequency = 20000;
  driver.init();

  // Init encoder
  encoder.init(&MotorGo::hspi);

  motor.linkDriver(&driver);
  motor.linkSensor(&encoder);
  motor.voltage_limit = channel_config.voltage_limit;
  motor.controller = MotionControlType::torque;
  motor.torque_controller = TorqueControlType::voltage;
  motor.init();

  Serial.println("Initialized Motor Channel");
  initialized = true;
}

void MotorGo::MotorChannel::loop()
{
  if (initialized)
  {
    motor.move();
  }
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

  // Set the target voltage, using target as a percentage of the voltage limit
  set_target_voltage(target_power * driver.voltage_power_supply);
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

void MotorGo::MotorChannel::set_control_mode(MotorGo::ControlMode control_mode)
{
  // Do nothing if the control mode is already set
  if (this->control_mode == control_mode)
  {
    return;
  }

  // Save control mode
  this->control_mode = control_mode;

  //   Switch for control mode
  switch (control_mode)
  {
    case MotorGo::ControlMode::Voltage:
      motor.torque_controller = TorqueControlType::voltage;
      motor.controller = MotionControlType::torque;
      break;
    case MotorGo::ControlMode::Velocity:
      motor.torque_controller = TorqueControlType::voltage;
      motor.controller = MotionControlType::velocity;
      break;
    case MotorGo::ControlMode::Position:
      motor.torque_controller = TorqueControlType::voltage;
      motor.controller = MotionControlType::angle;
      break;
    case MotorGo::ControlMode::VelocityOpenLoop:
      motor.torque_controller = TorqueControlType::voltage;
      motor.controller = MotionControlType::velocity_openloop;
      break;
    default:
      Serial.println("Invalid control mode");
      break;
  }
}

MotorGo::ControlMode MotorGo::MotorChannel::get_control_mode()
{
  return control_mode;
}

void MotorGo::MotorChannel::set_target_voltage(float target)
{
  target_voltage = target;
  motor.move(target_voltage);
}

void MotorGo::MotorChannel::set_target_velocity(float target)
{
  target_velocity = target;

  //   if (velocity_limit_enabled)
  //   {
  //     target_velocity =
  //         _constrain(target_velocity, -velocity_limit, velocity_limit);
  //   }

  // If the control mode is velocity open loop, move the motor
  // If closed loop velocity, move the motor only if PID params are set
  switch (control_mode)
  {
    case MotorGo::ControlMode::VelocityOpenLoop:
      //   motor.move(target_velocity);
      Serial.println("Velocity Open Loop not implemented");
      break;
    case MotorGo::ControlMode::Velocity:
      if (pid_velocity_enabled)
      {
        motor.move(target_velocity);
      }
      else
      {
        Serial.println("PID loop not configured for velocity control");
        disable();
      }
      break;
  }
}

void MotorGo::MotorChannel::enable()
{
  // Enable the motor
  motor.enable();
}

void MotorGo::MotorChannel::disable()
{
  // Disable the motor
  motor.disable();
}

void MotorGo::MotorChannel::set_velocity_controller(
    MotorGo::PIDParameters params)
{
  motor.PID_velocity.P = params.p;
  motor.PID_velocity.I = params.i;
  motor.PID_velocity.D = params.d;
  motor.PID_velocity.output_ramp = params.output_ramp;
  //   motor.PID_velocity.limit = params.limit;
  motor.LPF_velocity.Tf = params.lpf_time_constant;

  pid_velocity_enabled = true;
}
