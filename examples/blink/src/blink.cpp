#include <Arduino.h>
#include <motorgo_plink.h>

// Define LEDs
int LED_1 = 44;
int LED_2 = 43;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  //   Double blink at start
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);

  delay(500);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);

  delay(500);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);

  delay(500);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);

  delay(500);

  delay(3000);
}

void loop()
{
  // Blink both LEDS for a second
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);

  Serial.println("On");

  delay(1000);

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);

  Serial.println("Off");

  delay(1000);
}