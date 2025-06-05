#include "Seg7.h"

//0-9
const uint8_t segNumVal[10] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B};

uint8_t* seg7Pins = NULL;

// Initialize the 7-segment display with the given pin numbers
void seg7_init(const uint8_t* pins) {
    seg7Pins = (uint8_t*)pins;
    uint8_t i;
    for (i = 0; i < 7; i++) {
        pinMode(seg7Pins[i], OUTPUT); // Set each pin as an output
        digitalWrite(seg7Pins[i], HIGH); // Initialize all segments to HIGH
    }
}

// Display a number on the 7-segment display
void seg7_display(uint8_t num) {
    uint8_t bit = 0x40;
    uint8_t i;

    // Sequently control each part
    for (i = 0; i < 7; i++) {
        if (segNumVal[num] & bit) {
            digitalWrite(seg7Pins[i], LOW); // Turn on the segment
        } else {
            digitalWrite(seg7Pins[i], HIGH); // Turn off the segment
        }
        bit >>= 1; // Move to the next bit
    }
}
