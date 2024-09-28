#include "DisplayManager.h"

DisplayManager::DisplayManager(const int& latchPin, const int& clockPin, const int& dataPin, const int& outputEnablePin)
  : latchPin(latchPin), clockPin(clockPin), dataPin(dataPin), outputEnablePin(outputEnablePin){
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(outputEnablePin, OUTPUT);
}

void DisplayManager::showDigit(const int& digit){
  // Show the digit on the lcd
  writeByte(digits[digit]);
  
  // update the last shown digit
  lastShownDigit = digit;
 
}

void DisplayManager::showPoint(const bool& show){
  if (show) {
    // use the lastShownDigit and add the point (update the bit)
    byte digitWithPoint = lastShownDigit ^ B00000001;

    // show the updated digit
    writeByte(digitWithPoint);
  } else {

    // Simplay show (write) the last shown digit
    writeByte(lastShownDigit);
  }
}

void DisplayManager::setBrightness(const int& brightness){
  if (brightness < 0 && brightness > 255) {
    return;
  }
  
  // Update the outputEnablePin to alter the brightness
  analogWrite(outputEnablePin, 255 - brightness);
}

void DisplayManager::writeByte(byte b){
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // write out the byte
  shiftOut(dataPin, clockPin, LSBFIRST, b);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);

}