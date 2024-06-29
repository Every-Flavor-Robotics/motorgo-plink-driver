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
}

void loop()
{
  // Print data from the encoders
  Serial.print("Motor 1: ");
  Serial.print(motor1.get_position());
  Serial.print(", ");
  Serial.print(motor1.get_velocity());

  Serial.print("\tMotor 2: ");
  Serial.print(motor2.get_position());
  Serial.print(", ");
  Serial.print(motor2.get_velocity());

  Serial.print("\tMotor 3: ");
  Serial.print(motor3.get_position());
  Serial.print(", ");
  Serial.print(motor3.get_velocity());

  Serial.print("\tMotor 4: ");
  Serial.print(motor4.get_position());
  Serial.print(", ");
  Serial.print(motor4.get_velocity());

  Serial.println();

  delay(50);
}
