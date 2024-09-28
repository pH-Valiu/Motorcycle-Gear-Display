#include "GearApproximater.h"
#include "DisplayManager.h"

#define velocityPin A0
#define revolutionPin A5

#define displayLatchPin 2
#define displayClockPin 3
#define displayDataPin 4
#define displayOutputEnablePin 5

GearApproximater* gearApproximater;
DisplayManager* displayManager;

int lastGear = 0;


void setup(){
  pinMode(velocityPin, INPUT);
  pinMode(revolutionPin, INPUT);
  pinMode(displayLatchPin, OUTPUT);
  pinMode(displayClockPin, OUTPUT);
  pinMode(displayDataPin, OUTPUT);
  pinMode(displayOutputEnablePin, OUTPUT);

  Serial.begin(9600);

  // Initialize GearApproximater
  gearApproximater = new GearApproximater(createTireSpecs(), createMotoSpecs());

  // Initialize DisplayManager
  displayManager = new DisplayManager(displayLatchPin, displayClockPin, displayDataPin, displayOutputEnablePin);
  displayManager->setBrightness(200);
  displayManager->showDigit(0);
  displayManager->showPoint(false);
}

void loop(){
  int rpmVoltage = analogRead(revolutionPin);
  int velocityVoltage = analogRead(velocityPin);

  int rpm = map(rpmVoltage, 0, 1023, 0, 9000);
  int vel = map(velocityVoltage, 0, 1023, 0, 200);

  int gear = gearApproximater->approximateGear(rpm, vel);

  if (lastGear != gear){
    lastGear = gear;
    Serial.println("Showing");
    displayManager->showDigit(gear);
    //if /rpm > 3500): displayManager->showPoint(true) else false;
    
  }
  

  Serial.print("velocity: ");Serial.print(vel);Serial.print("\t");
  Serial.print("revolution: ");Serial.print(rpm);Serial.print("\t");
  Serial.print("gear: ");Serial.print(gear);Serial.println("\t");

  delay(1000);

}