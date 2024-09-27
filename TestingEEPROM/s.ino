#include <EEPROM.h>

int velocityPin = A0;
int revolutionPin = A5;

void setup(){
  pinMode(velocityPin, INPUT);
  pinMode(revolutionPin, INPUT);

  int table[127][127];
  Serial.begin(9600);
  Serial.print("size of table: ");Serial.println(sizeof(table));
}

void loop(){
  int rpmVolt = analogRead(revolutionPin);
  int velVolt = analogRead(velocityPin);

  int rpm = map(rpmVolt, 0, 1024, 0, 9000);
  int vel = map(velVolt, 0, 1024, 0, 200);

  float gearRatio = calculateGearRatio(rpm, vel);
  int gear = approximateGear(gearRatio);

  Serial.print("velocity: ");Serial.print(vel);Serial.print("\t");
  Serial.print("revolution: ");Serial.print(rpm);Serial.print("\t");
  Serial.print("gearRatio: ");Serial.print(gearRatio);Serial.print("\t");
  Serial.print("gear: ");Serial.print(gear);Serial.println("\t");

}