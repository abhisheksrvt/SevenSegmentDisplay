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
int dataPin = 4;  // your data pin connected to 74HC164 ic
int clockPin = 5;  // your clock pin connected to 74HC164 ic
int digitPins[3] = {1, 13, 14};  // your digital pins connected to 3 digit display 

// Create an instance of the SevenSegmentDisplay class
SevenSegmentDisplay display(dataPin, clockPin, digitPins, SevenSegmentDisplay::COMMON_CATHODE);

// Variables to handle timing without delay()
unsigned long previousMillis = 0;
const long interval = 500; // 500 milliseconds
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
                display.intDisplay(456);
                break;
            case 1:
                display.strDisplay("HI ");
                break;
            case 2:
                display.floatDisplay(45.6);
                break;
            case 3:
                display.displayDash();
                break;
            case 4:
                display.strDisplay("ESP");
                break;
            case 5:
                display.floatDisplay(7.89);
                break;
        }

        // Move to the next state
        displayState = (displayState + 1) % 6;
    }

    // Continuously update the display to maintain the current display buffer
    display.updateDisplay();
}
