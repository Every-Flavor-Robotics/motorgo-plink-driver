#include <Arduino.h>
#include <motorgo_plink.h>

// Create an instance of the MotorGo Plink driver
MotorGo::MotorGoPlink motorgo_plink;

// Get easy references to the motor/enconder channels
MotorGo::MotorChannel& motor1 = motorgo_plink.ch1;
MotorGo::MotorChannel& motor2 = motorgo_plink.ch2;
MotorGo::MotorChannel& motor3 = motorgo_plink.ch3;
MotorGo::MotorChannel& motor4 = motorgo_plink.ch4;

void setup()
{
  Serial.begin(115200);

  //   Wait for the serial port to connect. Needed for native USB port only
  while (!Serial)
  {
    delay(10);
  }

  // Intialize the MotorGo Plink hardware
  motorgo_plink.init();

  // Configure stopping behavior for the motors
  motor1.set_brake();
  motor2.set_coast();
  motor3.set_brake();
  motor4.set_coast();
}

void loop()
{
  // Set the power of the motors
  //   Ramp all motors up to full power
  for (float i = 0; i < 1.0; i += 0.01)
  {
    motor1.set_power(i);
    motor2.set_power(i);
    motor3.set_power(i);
    motor4.set_power(i);
    delay(50);

    // Print velocity of all motors
    Serial.print("Motor 1: ");
    Serial.print(motor1.get_velocity());
    Serial.print("\tMotor 2: ");
    Serial.print(motor2.get_velocity());
    Serial.print("\tMotor 3: ");
    Serial.print(motor3.get_velocity());
    Serial.print("\tMotor 4: ");
    Serial.println(motor4.get_velocity());
  }

  //   Set to zero power
  motor1.set_power(0);
  motor2.set_power(0);
  motor3.set_power(0);
  motor4.set_power(0);

  delay(500);

  //   Ramp all motors down to full reverse
  for (float i = 0; i > -1.0; i -= 0.01)
  {
    motor1.set_power(i);
    motor2.set_power(i);
    motor3.set_power(i);
    motor4.set_power(i);
    delay(50);

    // Print velocity of all motors
    Serial.print("Motor 1: ");
    Serial.print(motor1.get_velocity());
    Serial.print("\tMotor 2: ");
    Serial.print(motor2.get_velocity());
    Serial.print("\tMotor 3: ");
    Serial.print(motor3.get_velocity());
    Serial.print("\tMotor 4: ");
    Serial.println(motor4.get_velocity());
  }

  //   Set to zero power
  motor1.set_power(0);
  motor2.set_power(0);
  motor3.set_power(0);
  motor4.set_power(0);

  delay(500);
}
