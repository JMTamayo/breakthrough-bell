#include <Arduino.h>

#include "config/conf.h"
#include "logging/logger.h"

#include "controllers/timer.h"

#include "io/buzzers/active_buzzer.h"
#include "io/displays/oled_i2c.h"
#include "io/switches/push_switch.h"

buzzers::ActiveBuzzer *activeBuzzer;

displays::OLED_I2C *oledDisplay;

switches::PushSwitch *runPushSwitch;
switches::PushSwitch *modePushSwitch;
switches::PushSwitch *upPushSwitch;
switches::PushSwitch *downPushSwitch;

controllers::Timer *timer;

void setup() {
  logging::logger->Initialize();
  logging::logger->Info("Setting up system");

  activeBuzzer = new buzzers::ActiveBuzzer(config::ACTIVE_BUZZER_PIN);

  oledDisplay = new displays::OLED_I2C(
      config::OLED_DISPLAY_WIDTH, config::OLED_DISPLAY_HEIGHT,
      config::OLED_DISPLAY_RESET_PIN, config::OLED_DISPLAY_ADDRESS);

  runPushSwitch = new switches::PushSwitch(config::PUSH_SWITCH_RUN_PIN);
  modePushSwitch = new switches::PushSwitch(config::PUSH_SWITCH_MODE_PIN);
  upPushSwitch = new switches::PushSwitch(config::PUSH_SWITCH_UP_PIN);
  downPushSwitch = new switches::PushSwitch(config::PUSH_SWITCH_DOWN_PIN);

  timer = new controllers::Timer(config::DEFAULT_TIMER_DURATION_MS,
                                 activeBuzzer, runPushSwitch, modePushSwitch,
                                 upPushSwitch, downPushSwitch, oledDisplay);

  oledDisplay->MainScreen();
  delay(3000);

  logging::logger->Info("System initialized successfully");
}

void loop() { timer->Do(); }
