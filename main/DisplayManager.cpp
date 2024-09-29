#include "DisplayManager.h"

DisplayManager::DisplayManager(const Pins& p) 
  : pinOut {p.pinG, p.pinF, p.pinE, p.pinD, p.pinC, p.pinB, p.pinA, p.pinDP} {
  
  // Set the pinMode for all pins to OUTPUT
  for (int i=0; i < 8; i++){
    pinMode(pinOut[i], OUTPUT);
  }
}


void DisplayManager::showDigit(const int& digit){
  // Only update digit, if it differes to the last digit
  if (lastShownDigit != digit){
    
    // create temp digit-bit buffer
    byte digitAsByte = digits[digit];
    digitAsByte = digitAsByte >> 1;

    for (int i=0; i<7; i++){
      // For the current pin, decide whether to show or hide the led
      bool show = 1 & digitAsByte;

      digitalWrite(pinOut[i], show);

      // the temp digit-bit buffer to shift one bit to the right 
      digitAsByte = digitAsByte >> 1;
    }

    // update the last shown digit
    lastShownDigit = digit;
  }
}

void DisplayManager::showPoint(const bool& show){
  if (isPointOn != show){
    // pinOut[7] is pinDP
    digitalWrite(pinOut[7], show);

    // update isPointOn
    isPointOn = show;
  }
  
}

DisplayManager::Pins createPinOut(){
  struct DisplayManager::Pins p = {2, 3, 4, 5, 6, 7, 8, 9};
  return p;
}