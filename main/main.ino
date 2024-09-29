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
  long start = micros();

  int rpmVoltage = analogRead(revolutionPin);
  int velocityVoltage = analogRead(velocityPin);

  int rpm = map(rpmVoltage, 0, 1023, 0, 9000);
  int vel = map(velocityVoltage, 0, 1023, 0, 200);

  int gear = gearApproximater->approximateGear(rpm, vel);

  displayManager->showDigit(gear);

  displayManager->showPoint(showPointLogic(rpm, gear));

  long end = micros();
  Serial.print("velocity: ");Serial.print(vel);Serial.print("\t");
  Serial.print("revolution: ");Serial.print(rpm);Serial.print("\t");
  Serial.print("gear: ");Serial.print(gear);Serial.print("\t\t");
  Serial.print("loop took: ");Serial.print((end-start));Serial.println(" micros\t");

  // go to sleep if rpm is 0
  //if (rpm == 0){
  //  LowPower.deepSleep();
  //}

}

bool showPointLogic(const int& rpm, const int& gear){
  switch (gear) {
    case 1:
      return rpm > 3000;
    case 2:
      return (rpm < 1500) || (rpm > 4000);
    case 3:
      return (rpm < 2800) || (rpm > 4500);
    case 4:
      return (rpm < 3200) || (rpm > 5000);
    case 5:
      return (rpm < 3500) || (rpm > 6000);
    case 6:
      return rpm < 4000;
    default:
      return false;
  }
}