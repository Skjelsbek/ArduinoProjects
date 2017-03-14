#include "Stepper.h"
int stepsPerRev = 32;

// IN1 - IN4 på pin 8 - 11
Stepper myStepper(stepsPerRev, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(1100);
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
}

void loop() {
 while (digitalRead(12) == 1) {
  myStepper.step(2048);   
 }
 while (digitalRead(13) == 1) {
  myStepper.step(-2048);  
 }  
}
