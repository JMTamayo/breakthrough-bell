#include <Arduino.h>

#include "config/conf.h"
#include "logging/logger.h"

#include "io/buzzers/active_buzzer.h"
#include "io/leds/led.h"

leds::Led *builtinLed;
buzzers::ActiveBuzzer *activeBuzzer;

void setup() {
  logging::logger->Initialize();
  logging::logger->Info("Setting up system");

  builtinLed = new leds::Led(config::BUILTIN_LED_PIN);
  activeBuzzer = new buzzers::ActiveBuzzer(config::ACTIVE_BUZZER_PIN);

  logging::logger->Info("System initialized successfully");
}

void loop() {
  logging::logger->Info("Loop iteration started");

  activeBuzzer->AlarmClock();
  delay(5000);

  logging::logger->Info("Loop iteration finished");
}
