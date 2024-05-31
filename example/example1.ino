// Author Information-
// Author: Abhishek Srivastava
// linkedin: @abhisheksrvt
// github: @abhisheksrvt
// Contact: srvt.abhishek@gmail.com
// Version: 1.0
// Date: May 31, 2024
// License: MIT License

#include <Arduino.h>
#include "SevenSegmentDisplay.h"

// Pin definitions
int dataPin = 4;
int clockPin = 5;
int digitPins[3] = {1, 13, 14};

// Create an instance of the SevenSegmentDisplay class
// Specify the display type: SevenSegmentDisplay::COMMON_CATHODE or SevenSegmentDisplay::COMMON_ANODE
SevenSegmentDisplay display(dataPin, clockPin, digitPins, SevenSegmentDisplay::COMMON_CATHODE);

// Variables to handle timing without delay()
unsigned long previousMillis = 0;
const long interval = 1000; // 1 second
int displayState = 0;

void setup() {
    // Initialize the display (optional, if any initialization is needed)
}

void loop() {
    unsigned long currentMillis = millis();

    // Update the display buffer if interval has passed
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Cycle through different display modes
        switch (displayState) {
            case 0:
                display.intDisplay(123);
                break;
            case 1:
                display.strDisplay("P1 ");
                break;
            case 2:
                display.floatDisplay(12.3);
                break;
            case 3:
                display.displayDash();
                break;
        }

        // Move to the next state
        displayState = (displayState + 1) % 4;
    }

    // Continuously update the display to maintain the current display buffer
    display.updateDisplay();
}
