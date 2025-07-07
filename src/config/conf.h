#pragma once

#include <Arduino.h>

namespace config {

// Project Configuration parameters:

extern const String FIRMWARE_VERSION; // Firmware version

// Serial Configuration parameters:
extern const unsigned long
    DEFAULT_BAUD_RATE; // Default baud rate for serial communication

// I/O Pin Labeling:
extern const unsigned int
    ACTIVE_BUZZER_PIN; // Active buzzer pin for microcontroller

extern const unsigned int
    PUSH_SWITCH_CONTROL_PIN; // Pin for control push switch

extern const unsigned int PUSH_SWITCH_UP_PIN; // Pin for up push switch

extern const unsigned int PUSH_SWITCH_DOWN_PIN; // Pin for down push switch

// SCL and SDA pins for I2C communication are defined in the board
// configuration. For Arduino UNO R3, SCL is on analog pin 5 and SDA is on
// analog pin 4.

// Controller Configuration parameters:
extern const unsigned long
    DEFAULT_TIMER_DURATION_MS; // Default timer duration in milliseconds

// Display Configuration parameters:
extern const unsigned int OLED_DISPLAY_WIDTH; // Width of OLED display

extern const unsigned int OLED_DISPLAY_HEIGHT; // Height of OLED display

extern const unsigned int OLED_DISPLAY_ADDRESS; // Address of OLED display

extern const int OLED_DISPLAY_RESET_PIN; // Reset pin of OLED display

// Push Switch Configuration parameters:
extern const long
    CONTROL_BUTTON_DEBOUNCE_DELAY_MS; // Debounce delay for control button

extern const long
    CONTROL_BUTTON_HELD_THRESHOLD_MS; // Held threshold for control button

} // namespace config