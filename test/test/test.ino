#include "pins.h"

#define BUZZER 11
#define RECIEVER 10
#define ECHO 9
#define TRIG 8
int stepper_pins[] = {3,5,4,2}; // order of which in the pins need to be passed into Stepper class when initilizing it

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BUZZER, LOW);
}
