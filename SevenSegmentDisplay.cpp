#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay(int dataPin, int clockPin, int digitPins[3], DisplayType displayType)
    : dataPin(dataPin), clockPin(clockPin), displayType(displayType), count(0) {
    for (int i = 0; i < 3; i++) {
        this->digitPins[i] = digitPins[i];
        displayBuffer[i] = displayType == COMMON_CATHODE ? B00000000 : B11111111; // Initialize display buffer to blank
    }

    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    for (int i = 0; i < 3; i++) {
        pinMode(digitPins[i], OUTPUT);
    }

    // Common cathode patterns
    byte cathodeTable[17] = {
        B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000,
        B11111110, B11110110, B10011110, B11101110, B01111100, B10011100, B10001110, B00111010,
        B00101010
    };

    // Initialize the character table for A-Z
    char cathodeCharTable[26] = {
        B11101110, B11111110, B10011100, B11111100, B10011110, B10001110, B10111110, B01101110,
        B01100000, B01110000, B01101110, B00011100, B11101100, B11101110, B11111100, B11001110,
        B11100110, B11101010, B11011010, B00011110, B00111110, B01111110, B01111110, B01111110,
        B01101110, B11001110
    };

    // Copy patterns to class members
    for (int i = 0; i < 17; i++) {
        table[i] = displayType == COMMON_CATHODE ? cathodeTable[i] : invertByte(cathodeTable[i]);
    }
    for (int i = 0; i < 26; i++) {
        charTable[i] = displayType == COMMON_CATHODE ? cathodeCharTable[i] : invertByte(cathodeCharTable[i]);
    }
}

byte SevenSegmentDisplay::invertByte(byte b) {
    return ~b & B11111111;
}

void SevenSegmentDisplay::clearDisplay() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(digitPins[i], displayType == COMMON_CATHODE ? HIGH : LOW);
    }
}

void SevenSegmentDisplay::shiftOutData(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(clockPin, LOW);
        digitalWrite(dataPin, (data & (1 << i)) ? HIGH : LOW);
        digitalWrite(clockPin, HIGH);
    }
}

void SevenSegmentDisplay::intDisplay(long num) {
    int num1 = num / 100;
    int num2 = (num / 10) % 10;
    int num3 = num % 10;
    int numbers[3] = {num1, num2, num3};

    displayBuffer[0] = (numbers[0] == 0 && num < 100) ? (displayType == COMMON_CATHODE ? B00000000 : B11111111) : table[numbers[0]];
    displayBuffer[1] = (numbers[0] == 0 && numbers[1] == 0 && num < 10) ? (displayType == COMMON_CATHODE ? B00000000 : B11111111) : table[numbers[1]];
    displayBuffer[2] = table[numbers[2]];
}

void SevenSegmentDisplay::strDisplay(const char* chars) {
    for (int i = 0; i < 3; i++) {
        if (chars[i] >= 'A' && chars[i] <= 'Z') {
            displayBuffer[i] = charTable[chars[i] - 'A'];
        } else if (chars[i] >= '0' && chars[i] <= '9') {
            displayBuffer[i] = table[chars[i] - '0'];
        } else {
            displayBuffer[i] = displayType == COMMON_CATHODE ? B00000000 : B11111111; // Blank for unsupported characters
        }
    }
}

void SevenSegmentDisplay::floatDisplay(float num) {
    int intPart = (int)num;
    int fracPart = (int)((num - intPart) * 10);

    int numbers[3] = {intPart / 10, intPart % 10, fracPart};

    displayBuffer[0] = (numbers[0] == 0) ? (displayType == COMMON_CATHODE ? B00000000 : B11111111) : table[numbers[0]];
    displayBuffer[1] = table[numbers[1]] | (displayType == COMMON_CATHODE ? B00000001 : B11111110); // Add decimal point to the middle digit
    displayBuffer[2] = table[numbers[2]];
}

void SevenSegmentDisplay::displayDash() {
    byte dash = displayType == COMMON_CATHODE ? B00000010 : B11111101;
    for (int i = 0; i < 3; i++) {
        displayBuffer[i] = dash; // Dash representation for both types
    }
}

void SevenSegmentDisplay::updateDisplay() {
    clearDisplay();
    shiftOutData(displayBuffer[count]);
    digitalWrite(digitPins[count], displayType == COMMON_CATHODE ? LOW : HIGH); // Adjust for display type
    count++;
    if (count == 3) {
        count = 0;
    }
    delay(2);   // try out various time delay according to your board's suitability
}
