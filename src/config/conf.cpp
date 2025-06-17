#include "conf.h"

namespace config {

const unsigned long DEFAULT_BAUD_RATE = 115200;

const unsigned int ACTIVE_BUZZER_PIN = 13;

const unsigned int PUSH_SWITCH_RUN_PIN = 2;

const unsigned int PUSH_SWITCH_MODE_PIN = 3;

const unsigned int PUSH_SWITCH_UP_PIN = 5;

const unsigned int PUSH_SWITCH_DOWN_PIN = 4;

const unsigned long DEFAULT_TIMER_DURATION_MS = 0;

const unsigned int OLED_DISPLAY_WIDTH = 128;

const unsigned int OLED_DISPLAY_HEIGHT = 32;

const unsigned int OLED_DISPLAY_ADDRESS = 0x3C;

const int OLED_DISPLAY_RESET_PIN = -1;

} // namespace config