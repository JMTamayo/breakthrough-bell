#include "conf.h"

namespace config {

const unsigned long DEFAULT_BAUD_RATE = 115200;

const unsigned int ACTIVE_BUZZER_PIN = 13;

const unsigned int PUSH_SWITCH_CONTROL_PIN = 4;

const unsigned int PUSH_SWITCH_UP_PIN = 2;

const unsigned int PUSH_SWITCH_DOWN_PIN = 3;

const unsigned long DEFAULT_TIMER_DURATION_MS = 5000;

const unsigned int OLED_DISPLAY_WIDTH = 128;

const unsigned int OLED_DISPLAY_HEIGHT = 32;

const unsigned int OLED_DISPLAY_ADDRESS = 0x3C;

const int OLED_DISPLAY_RESET_PIN = -1;

const long CONTROL_BUTTON_DEBOUNCE_DELAY_MS = 80;

const long CONTROL_BUTTON_HELD_THRESHOLD_MS = 300;

} // namespace config