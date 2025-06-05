#include "Seg7.h"

const uint8_t segPins[] = {5, 6, 7, 8, 9, 10, 11}; /* 7 segment display pins (a-g) */

uint8_t Num = 0;

void setup() {
    seg7_init(segPins); // Initialize the 7-segment display with the specified pins
}

void loop() {
    seg7_display(Num); // Display the current number on the 7-segment display
    Num++; // Increment the number
    if (Num > 9) { // Reset to 0 after reaching 9
        Num = 0;
    }
    delay(500); // Wait for 500ms before updating the display again
}

