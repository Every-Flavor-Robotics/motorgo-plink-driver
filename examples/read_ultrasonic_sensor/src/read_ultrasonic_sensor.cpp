#include <Arduino.h>
#include <Wire.h>
#include <motorgo_plink.h>

#define SENSOR_ADDRESS 0x57
#define START_RANGING 0x01

void setup()
{
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize I2C communication
  Wire.begin(SDA, SCL, 100000);  // Initialize I2C with custom SDA and SCL pins
}

void loop()
{
  // Start a ranging session by writing '1' to the sensor
  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(START_RANGING);
  Wire.endTransmission();

  // Wait for the sensor to complete the ranging
  delay(10);  // Adjust the delay as needed based on sensor timing

  // Request 3 bytes from the sensor
  Wire.requestFrom(SENSOR_ADDRESS, 3);

  // Check if 3 bytes were received
  if (Wire.available() == 3)
  {
    uint32_t distance = 0;

    // Read the 3 bytes and combine them
    distance |= Wire.read();  // Read the first byte
    distance <<= 8;           // Shift left by 8 bits
    distance |= Wire.read();  // Read the second byte
    distance <<= 8;           // Shift left by 8 bits
    distance |= Wire.read();  // Read the third byte

    // Convert the distance to millimeters
    float distance_mm = distance / 1000.0;

    // Print the distance
    Serial.print("Distance: ");
    Serial.print(distance_mm);
    Serial.println(" mm");
  }
  else
  {
    Serial.println("Failed to read distance from sensor");
  }

  // Wait a bit before the next reading
  delay(100);  // Adjust the delay as needed
}