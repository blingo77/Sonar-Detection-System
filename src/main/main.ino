#include <Stepper.h>

#include <IRremote.hpp>
#include "IRremote.h"
#include <SR04.h>
#include "SR04.h"

#include "pins.h"
#include "IRcodes.h"

#include "sonarCheck.hpp"

IRrecv irrecv(RECIEVER);
SR04 sonar = SR04(ECHO,TRIG); 
Stepper stepper(1000, stepper_pins[0], stepper_pins[1], stepper_pins[2], stepper_pins[3]);

unsigned long dist;

const int rolePerMin = 15;              // how fast the stepper motor turns
const int stepsPerRevolution = 1000;
int stepperAngle = 0;

bool power = false;
uint32_t lastDecodedIR = 0;

void setup() {

  stepper.setSpeed(rolePerMin);
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void checkForObj(unsigned long* dist, int angle){
  *dist = sonar.Distance();

  if(*dist < TARGET_RANGE)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("####OBJECT IN RANGE####");
    Serial.print("Distance (CM): ");
    Serial.println( *dist);
    Serial.print("Angle: ");
    Serial.println(angle);

  }
  else
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);   
  }

}

void stop(int stepperAngle){

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  if (stepperAngle != 0)
  {
    while(stepperAngle != 0)
    {
      Serial.println(stepperAngle);
      stepperAngle--;
      stepper.step(-3);
    }
  }
}

void start(int stepperAngle, unsigned long dist){

  Serial.println("starting");

  for(int i = 0; i <= 180; i++)
  {
    stepperAngle++;
    checkForObj(&dist, stepperAngle);
    stepper.step(6);
  }
  for(int i = 0; i <= 180; i++)
  {
    stepperAngle--;
    checkForObj(&dist, stepperAngle);
    stepper.step(-6);
  }

}

void loop() {
  
  if(irrecv.decode())
  {
    if(irrecv.decodedIRData.decodedRawData == POWER && lastDecodedIR == 0)
    {
      power = true;
      lastDecodedIR = irrecv.decodedIRData.decodedRawData;
    }
    else if(irrecv.decodedIRData.decodedRawData == POWER && lastDecodedIR == POWER)
    {
      power = false;
      lastDecodedIR = 0;
      Serial.println("OFF");
    }
    irrecv.resume();
  }

  if(power)
  {
    start(stepperAngle, dist);
  }
  else if(!power)
  {
    stop(stepperAngle);
  }

}
