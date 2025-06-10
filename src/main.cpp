#include <Arduino.h>

#include "config/conf.h"
#include "io/leds/leds.h"
#include "logging/logger.h"

leds::Led *builtinLed;

void setup() {
  logging::logger->Initialize();
  logging::logger->Info("Setting up system");

  builtinLed = new leds::Led(config::BUILTIN_LED_PIN);

  logging::logger->Info("System initialized successfully");
}

void loop() {
  logging::logger->Info("Loop iteration started");

  // TODO: Add main loop logic here

  logging::logger->Info("Loop iteration finished");
}
