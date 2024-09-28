#include "GearApproximater.h"

int velocityPin = A0;
int revolutionPin = A5;
GearApproximater* gearApproximater;


void setup(){
  pinMode(velocityPin, INPUT);
  pinMode(revolutionPin, INPUT);

  Serial.begin(9600);

  // Initialize GearApproximater
  gearApproximater = new GearApproximater(createTireSpecs(), createMotoSpecs());
}

void loop(){
  int rpmVoltage = analogRead(revolutionPin);
  int velocityVoltage = analogRead(velocityPin);

  int rpm = map(rpmVoltage, 0, 1023, 0, 9000);
  int vel = map(velocityVoltage, 0, 1023, 0, 200);

  int gear = gearApproximater->approximateGear(rpm, vel);

  Serial.print("velocity: ");Serial.print(vel);Serial.print("\t");
  Serial.print("revolution: ");Serial.print(rpm);Serial.print("\t");
  Serial.print("gear: ");Serial.print(gear);Serial.println("\t");
  delay(500);

}