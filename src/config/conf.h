#pragma once

namespace config {

// Serial Configuration parameters:
extern const unsigned long
    DEFAULT_BAUD_RATE; // Default baud rate for serial communication

// I/O Pin Labeling:
extern const unsigned int
    ACTIVE_BUZZER_PIN; // Active buzzer pin for microcontroller

extern const unsigned int PUSH_SWITCH_RUN_PIN; // Pin for run push switch

extern const unsigned int PUSH_SWITCH_MODE_PIN; // Pin for mode push switch

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

} // namespace config