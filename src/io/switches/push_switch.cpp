#include <Arduino.h>

#include "push_switch.h"

namespace switches {

const unsigned int PushSwitch::getPin() const { return this->pin; }

PushSwitch::PushSwitch(unsigned int pin) : pin(pin) {
  pinMode(this->getPin(), INPUT_PULLUP);
}

PushSwitch::~PushSwitch() {}

bool PushSwitch::IsPressed() const {
  return digitalRead(this->getPin()) == LOW;
}

} // namespace switches