#include "GearApproximater.h"
#include "DisplayManager.h"

#define velocityPin A0
#define revolutionPin A5

GearApproximater* gearApproximater;
DisplayManager* displayManager;



void setup(){
  pinMode(velocityPin, INPUT);
  pinMode(revolutionPin, INPUT);
  Serial.begin(9600);

  // Initialize GearApproximater
  gearApproximater = new GearApproximater(createTireSpecs(), createMotoSpecs());

  // Initialize DisplayManager
  displayManager = new DisplayManager(createPinOut());
  displayManager->showDigit(0);
  displayManager->showPoint(false);
}

void loop(){
  int rpmVoltage = analogRead(revolutionPin);
  int velocityVoltage = analogRead(velocityPin);

  int rpm = map(rpmVoltage, 0, 1023, 0, 9000);
  int vel = map(velocityVoltage, 0, 1023, 0, 200);

  int gear = gearApproximater->approximateGear(rpm, vel);

  displayManager->showDigit(gear);

  if (rpm >= 5000){
    displayManager->showPoint(true);
  }else {
    displayManager->showPoint(false);
  }


  Serial.print("velocity: ");Serial.print(vel);Serial.print("\t");
  Serial.print("revolution: ");Serial.print(rpm);Serial.print("\t");
  Serial.print("gear: ");Serial.print(gear);Serial.println("\t");

  delay(1000);
}