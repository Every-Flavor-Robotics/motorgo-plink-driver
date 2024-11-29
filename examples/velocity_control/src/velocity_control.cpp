#include <Arduino.h>
#include <motorgo_plink.h>

// Create an instance of the MotorGo Plink driver
MotorGo::MotorGoPlink motorgo_plink;

// Get easy references to the motor/enconder channels
MotorGo::MotorChannel& motor1 = motorgo_plink.ch1;

MotorGo::PIDParameters velocity_controller;

void setup()
{
  Serial.begin(115200);

  //   Wait for the serial port to connect. Needed for native USB port only
  while (!Serial)
  {
    delay(10);
  }

  velocity_controller.p = 4.0;
  velocity_controller.i = 0.1;

  // Intialize the MotorGo Plink hardware
  motorgo_plink.init();

  motor1.set_control_mode(MotorGo::ControlMode::Velocity);

  motor1.set_velocity_controller(velocity_controller);

  motor1.set_target_velocity(2);

  motor1.enable();
}

void loop()
{
  Serial.println(motor1.get_velocity(), 5);
  delay(500);
}
