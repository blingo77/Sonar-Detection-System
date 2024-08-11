#include <SR04.h>
#include "SR04.h"

/* Define the pin numbers */
#define GREEN 3
#define BLUE 4
#define RED 2
#define BUZZER 12
#define TRIG 9
#define ECHO 8

// create an object of the sonar sensor class
SR04 sonar = SR04(ECHO,TRIG); 

unsigned long dist;
int targetDist = 10;

void setup() {

  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

}

void checkObj(unsigned long distance)
{

  /*
    green needs to be turned off if red is being turned on,
    if not then the colors will mix and the RGB led will become yellow
  */
  if(distance <= targetDist){   //checks if a object is less than or equial to target_dist Cm close
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BUZZER, HIGH);
  }
  else{
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(BUZZER, LOW);
  }
}

void loop() {
  dist = sonar.Distance();
  checkObj(dist);
  Serial.print(dist);
  Serial.println(" cm");

}
