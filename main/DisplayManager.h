#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "Arduino.h"

/**
* This class handles the communication with the seven segment LCD
*
* Please call its constructor during the stup() phase on the Arduino
*/
class DisplayManager{
  public:
    // The struct for passing the pin numbers of the leds to the constructor
    struct Pins{
      int pinA;
      int pinB;
      int pinC;
      int pinD;
      int pinE;
      int pinF;
      int pinG;
      int pinDP;
    };
  
  private:

    // define the LED digit patterns, from 0 - 9
    // 1 = LED on, 0 = LED off, in this order:
    //                Mapping to      a,b,c,d,e,f,g,dp of Seven-Segment LED
    const byte digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11110110   // = 9
                             };

    // The actual internal storage of the pin numbers in mostly reverse order:
    // {pinG, pinF, pinE, pinD, pinC, pinB, pinA, pinDP}
    const int pinOut[8];

    // last shown digit (needed for efficient displaying)
    byte lastShownDigit = 0;

    // whether the point is on (neeeded for efficient displaying)
    bool isPointOn = 0;

  public:
    
    /**
    * Constructor has to be called during setup() stage of Arduino
    * @param pinOut this has to be a fully initialized Pins struct
    */
    DisplayManager(const Pins& pinOut);
    /**
    * Display the digit on the 74HC595
    * @param digit the digit to display: 0 to 9
    */
    void showDigit(const int& digit);
    
    /**
    * Decide whether to show or hide the point of the 74HC595 (DP)
    * @param show whether or not to show it
    */
    void showPoint(const bool& show);
};

/**
* Helper method to create Pins struct for default layout
* 
* Default is:
*
* pinA = 2, pinB = 3, pinC = 4, pinD = 5, pinE = 6, pinF = 7, pinG = 8, pinDP = 9
*/
DisplayManager::Pins createPinOut();

#endif