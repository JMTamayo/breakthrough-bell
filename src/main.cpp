#include <Arduino.h>

#include "config/conf.h"
#include "logging/logger.h"

#include "controllers/timer.h"

#include "io/buzzers/active_buzzer.h"
#include "io/displays/oled_i2c.h"
#include "io/switches/push_switch.h"

buzzers::ActiveBuzzer *activeBuzzer;

displays::OLED_I2C *oledDisplay;

switches::ControlButton *modeButton;
switches::ControlButton *upButton;
switches::ControlButton *downButton;

controllers::Timer *timer;

void setup() {
  logging::logger->Initialize();
  logging::logger->Info("Setting up system");

  activeBuzzer = new buzzers::ActiveBuzzer(config::ACTIVE_BUZZER_PIN);

  oledDisplay = new displays::OLED_I2C(
      config::OLED_DISPLAY_WIDTH, config::OLED_DISPLAY_HEIGHT,
      config::OLED_DISPLAY_RESET_PIN, config::OLED_DISPLAY_ADDRESS);

  modeButton = new switches::ControlButton(
      config::PUSH_SWITCH_CONTROL_PIN, config::CONTROL_BUTTON_DEBOUNCE_DELAY_MS,
      config::CONTROL_BUTTON_HELD_THRESHOLD_MS);

  upButton = new switches::ControlButton(
      config::PUSH_SWITCH_UP_PIN, config::CONTROL_BUTTON_DEBOUNCE_DELAY_MS,
      config::CONTROL_BUTTON_HELD_THRESHOLD_MS);

  downButton = new switches::ControlButton(
      config::PUSH_SWITCH_DOWN_PIN, config::CONTROL_BUTTON_DEBOUNCE_DELAY_MS,
      config::CONTROL_BUTTON_HELD_THRESHOLD_MS);

  timer =
      new controllers::Timer(config::DEFAULT_TIMER_DURATION_MS, activeBuzzer,
                             modeButton, upButton, downButton, oledDisplay);

  logging::logger->Info("System initialized successfully");

  oledDisplay->HomeScreen();
  modeButton->RestartTime();
}

void loop() { timer->Do(); }
