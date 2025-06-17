#include <Arduino.h>

#include "active_buzzer.h"

namespace buzzers {

const unsigned int ActiveBuzzer::getPin() const { return this->pin; }

ActiveBuzzer::ActiveBuzzer(unsigned int pin) : pin(pin) {
  pinMode(this->getPin(), OUTPUT);
  digitalWrite(this->getPin(), LOW);
}

ActiveBuzzer::~ActiveBuzzer() {}

void ActiveBuzzer::Beep() {
  digitalWrite(this->getPin(), HIGH);
  delay(50);
  digitalWrite(this->getPin(), LOW);
  delay(50);
}

void ActiveBuzzer::AlarmClock() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      this->Beep();
    }
    delay(1000);
  }
}

} // namespace buzzers