#include <Arduino.h>

#include "../../logging/logger.h"

#include "push_switch.h"

namespace switches {

const unsigned int Button::getPin() const { return this->pin; }

Button::Button(unsigned int pin) : pin(pin) {
  pinMode(this->getPin(), INPUT_PULLUP);
}

Button::~Button() {}

bool Button::IsPressed() const { return digitalRead(this->getPin()) == LOW; }

const unsigned long ControlButton::getDebounceDelayMs() const {
  return this->debounceDelayMs;
}

const unsigned long ControlButton::getHeldThresholdMs() const {
  return this->heldThresholdMs;
}

unsigned long ControlButton::getUpdatedAtMs() const {
  return this->updatedAtMs;
}

ControlButton::ControlButton(const unsigned int pin,
                             const unsigned long debounceDelayMs,
                             const unsigned long heldThresholdMs)
    : Button(pin), debounceDelayMs(debounceDelayMs),
      heldThresholdMs(heldThresholdMs), updatedAtMs(millis()) {}

ControlButton::~ControlButton() {}

void ControlButton::RestartTime() { this->updatedAtMs = millis(); }

ControlButtonStatus ControlButton::GetStatus() {
  ControlButtonStatus status;

  const unsigned long timeSincePressedMs = millis() - this->getUpdatedAtMs();
  const bool isPressed = this->IsPressed();

  if (!isPressed) {
    if (timeSincePressedMs < this->getDebounceDelayMs()) {
      status = CONTROL_BUTTON_NOT_PRESSED;

    } else if (timeSincePressedMs >= this->getDebounceDelayMs() &&
               timeSincePressedMs < this->getHeldThresholdMs()) {
      status = CONTROL_BUTTON_PRESSED;

    } else {
      status = CONTROL_BUTTON_HELD;
    }

    this->RestartTime();

  } else {
    if (timeSincePressedMs >= this->getHeldThresholdMs()) {
      status = CONTROL_BUTTON_HELD;
      this->RestartTime();

    } else {
      status = CONTROL_BUTTON_NOT_PRESSED;
    }
  }

  return status;
}
} // namespace switches