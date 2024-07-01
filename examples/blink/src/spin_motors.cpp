#include <Arduino.h>
#include <motorgo_plink.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(P38, OUTPUT);
  pinMode(P47, OUTPUT);
  pinMode(P7, OUTPUT);
  pinMode(P4, OUTPUT);

  //   Double blink at start
  digitalWrite(P38, HIGH);
  digitalWrite(P47, HIGH);
  digitalWrite(P7, HIGH);
  digitalWrite(P4, HIGH);

  delay(500);
  digitalWrite(P38, LOW);
  digitalWrite(P47, LOW);
  digitalWrite(P7, HIGH);
  digitalWrite(P4, HIGH);

  delay(500);
  digitalWrite(P38, HIGH);
  digitalWrite(P47, HIGH);
  digitalWrite(P7, HIGH);
  digitalWrite(P4, HIGH);

  delay(500);
  digitalWrite(P38, LOW);
  digitalWrite(P47, LOW);
  digitalWrite(P7, LOW);
  digitalWrite(P4, LOW);

  delay(500);

  delay(3000);
}

void loop()
{
  // Blink both LEDS for a second
  digitalWrite(P38, HIGH);
  digitalWrite(P47, HIGH);
  digitalWrite(P7, HIGH);
  digitalWrite(P4, HIGH);

  Serial.println("On");

  delay(1000);

  digitalWrite(P38, LOW);
  digitalWrite(P47, LOW);
  digitalWrite(P7, LOW);
  digitalWrite(P4, LOW);

  Serial.println("Off");

  delay(1000);
}