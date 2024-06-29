#include <Arduino.h>
#include <hp_BH1750.h>  //  include the library
#include <motorgo_plink.h>

#include "Wire.h"

hp_BH1750 BH1750;  //  create the sensor

void setup()
{
  // Setup Wire
  Wire.begin(SDA, SCL, 100000);

  // put your setup code here, to run once:
  Serial.begin(115200);
  bool avail = BH1750.begin(BH1750_TO_GROUND,
                            &Wire);  // init the sensor with address pin
  // be be "false" if no sensor found
  if (!avail)
  {
    Serial.println("No BH1750 sensor found!");
    while (true)
    {
    };
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  BH1750.start();               // starts a measurement
  float lux = BH1750.getLux();  //  waits until a conversion finished
  Serial.println(lux);
}