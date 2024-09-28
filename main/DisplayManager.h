#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "Arduino.h"

/**
* This class handles the communication with the 74HC595 to display digits at the LCD
*
* Please call its constructor during the stup() phase on the Arduino
*
* Also, please make sure that the outputEnablePin is PWM
*/
class DisplayManager{
  private:
    // connect to the ST_CP of 74HC595 (latch pin)
    const int latchPin;

    // connect to the SH_CP of 74HC595 (clock pin)
    const int clockPin;

    // connect to the DS of 74HC595 (data pin)
    const int dataPin;

    // connect to the OE of 74HC595 (output enable pin).
    const int outputEnablePin;

    // define the LED digit patterns, from 0 - 9
    // 1 = LED on, 0 = LED off, in this order:
    //                74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7 
    //                Mapping to      a,b,c,d,e,f,g of Seven-Segment LED
    const byte digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };

    // last shown digit (needed for point display)
    byte lastShownDigit;

  public:
    /**
    * Constructor has to be called during setup() stage of Arduino
    * @param outputEnablePin this has to be a PWM pin
    */
    DisplayManager(const int& latchPin, const int& clockPin, const int& dataPin, const int& outputEnablePin);
    
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

    /**
    * Set the brightness of the display
    * @param brightness value between 0 (out) and 255 (full illumination)
    */
    void setBrightness(const int& brightness);
  
  private:
  /**
  * Writes the byte in LSBFIRST orientation onto the 74HC595
  * @param b the byte to write (LSBFIRST)
  */
  void writeByte(byte b);
};

#endif