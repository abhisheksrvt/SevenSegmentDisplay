# SevenSegmentDisplay Library

## Description
The `SevenSegmentDisplay` library provides an easy-to-use interface for controlling a 3-digit 7-segment display using an ESP8266 WiFi SoC and a 74HC164 shift register IC. The library supports both common cathode and common anode displays and includes functions to display integers, strings, floats, and dashes.

## Features
- Support for both common cathode and common anode displays
- Display integers
- Display strings (A-Z, 0-9)
- Display floating point numbers with one decimal place
- Display dashes "---"
- Non-blocking update using `millis()` for timing

## Getting Started

### Hardware Setup
- Connect the data and clock pins of the 74HC164 IC to the specified pins on the ESP8266.
- Connect the digit control pins to the corresponding GPIO pins on the ESP8266 or other microcontroller board.
- Ensure the common pin (cathode or anode) of each 7-segment display digit is connected appropriately.

### Software Setup

## Installation
To install the library, download or clone the repository into your Arduino libraries folder.

```bash
git clone https://github.com/abhisheksrvt/SevenSegmentDisplay.git
```

1. **Include the Library**
    ```cpp
    #include <Arduino.h>
    #include "SevenSegmentDisplay.h"
    ```

2. **Define Pin Connections and Create Display Instance**
    ```cpp
    // Pin definitions
    int dataPin = 4;
    int clockPin = 5;
    int digitPins[3] = {1, 13, 14};

    // Create an instance of the SevenSegmentDisplay class
    SevenSegmentDisplay display(dataPin, clockPin, digitPins, SevenSegmentDisplay::COMMON_CATHODE);
    ```

3. **Use Display Functions**
    ```cpp
    void setup() {
        // No setup needed for the display
    }

    void loop() {
        // Example usage
        display.intDisplay(123);
        delay(1000);
        display.strDisplay("P1 ");
        delay(1000);
        display.floatDisplay(12.3);
        delay(1000);
        display.displayDash();
        delay(1000);
    }
    ```

### Example Code
Here is an example sketch that demonstrates using the library to display an integer, a string, a float, and dashes with a 1-second interval between each display:

```cpp
#include <Arduino.h>
#include "SevenSegmentDisplay.h"

// Pin definitions
int dataPin = 4;
int clockPin = 5;
int digitPins[3] = {1, 13, 14};

// Create an instance of the SevenSegmentDisplay class
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

### Functions

- **`void intDisplay(int num)`**: Displays an integer on the display.
- **`void strDisplay(const char* str)`**: Displays a string on the display.
- **`void floatDisplay(float num)`**: Displays a floating-point number on the display.
- **`void displayDash()`**: Displays three dashes ("---") on the display.
- **`void updateDisplay()`**: Updates the display buffer to maintain the current state.

## License
This library is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Author
Created by Abhishek Srivastava. Feel free to reach out at [srvt.abhishek@example.com] for any questions or feedback.

## Contributing
Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.
```

### LICENSE (MIT License)

```plaintext
MIT License

Copyright (c) 2024 Abhishek Srivastava

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```


