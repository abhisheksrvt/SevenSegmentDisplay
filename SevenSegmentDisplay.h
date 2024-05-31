// Author Information-
// Author: Abhishek Srivastava
// linkedin: @abhisheksrvt
// Contact: srvt.abhishek@gmail.com
// Version: 1.0
// Date: May 31, 2024


#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H

#include <Arduino.h>

class SevenSegmentDisplay {
public:
    enum DisplayType { COMMON_CATHODE, COMMON_ANODE };

    SevenSegmentDisplay(int dataPin, int clockPin, int digitPins[3], DisplayType displayType);
    void intDisplay(long num);
    void strDisplay(const char* chars);
    void floatDisplay(float num);
    void displayDash();
    void updateDisplay();

private:
    int dataPin;
    int clockPin;
    int digitPins[3];
    int count;
    DisplayType displayType;
    byte table[17];
    byte charTable[26];
    byte displayBuffer[3];
    void clearDisplay();
    void shiftOutData(uint8_t data);
    byte invertByte(byte b); // Function to invert byte for common anode
};

#endif // SEVENSEGMENTDISPLAY_H
