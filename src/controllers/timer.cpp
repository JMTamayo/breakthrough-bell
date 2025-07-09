#include <Arduino.h>

#include "timer.h"

#include "../config/conf.h"
#include "../logging/logger.h"

#include "../io/buzzers/active_buzzer.h"
#include "../io/switches/push_switch.h"

namespace controllers {

TimerState Timer::getState() const { return this->state; }

void Timer::setState(TimerState state) { this->state = state; }

String Timer::getStateString() const {
  switch (this->getState()) {
  case TIMER_STATE_PAUSED:
    return "Paused";
  case TIMER_STATE_RUNNING:
    return "Running";
  case TIMER_STATE_CONFIG_SECONDS:
    return "Config: Seconds";
  case TIMER_STATE_CONFIG_MINUTES:
    return "Config: Minutes";
  case TIMER_STATE_CONFIG_HOURS:
    return "Config: Hours";
  default:
    return "Unknown";
  }
}

unsigned long Timer::getDurationMs() const { return this->durationMs; }

void Timer::setDurationMs(unsigned long durationMs) {
  this->durationMs = durationMs;
}

unsigned long Timer::getRemainingTimeMs() const {
  return this->remainingTimeMs;
}

void Timer::setRemainingTimeMs(unsigned long remainingTimeMs) {
  this->remainingTimeMs = remainingTimeMs;
}

void Timer::updateRemainingTimeMs() {
  unsigned long now = millis();
  unsigned long elapsedTimeMs = now - this->getUpdatedAtMs();

  logging::logger->Info("Elapsed time: " + String(elapsedTimeMs) + " ms");

  if (elapsedTimeMs >= this->getRemainingTimeMs()) {
    this->remainingTimeMs = 0;
  } else {
    this->remainingTimeMs = this->getRemainingTimeMs() - elapsedTimeMs;
  }

  this->setUpdatedAtMs(now);
}

unsigned long Timer::getUpdatedAtMs() const { return this->updatedAtMs; }

void Timer::setUpdatedAtMs(unsigned long updatedAtMs) {
  this->updatedAtMs = updatedAtMs;
}

buzzers::ActiveBuzzer *Timer::getActiveBuzzer() const {
  return this->activeBuzzer;
}

switches::ControlButton *Timer::getModeButton() const {
  return this->modeButton;
}

switches::ControlButton *Timer::getUpButton() const { return this->upButton; }

switches::ControlButton *Timer::getDownButton() const {
  return this->downButton;
}

displays::OLED_I2C *Timer::getDisplay() const { return this->display; }

unsigned int Timer::getHours() const {
  return this->getRemainingTimeMs() / 3600000;
}

unsigned int Timer::getMinutes() const {
  return (this->getRemainingTimeMs() % 3600000) / 60000;
}

unsigned int Timer::getSeconds() const {
  return (this->getRemainingTimeMs() % 60000) / 1000;
}

void Timer::ignoreMillis() {
  this->setRemainingTimeMs((this->getRemainingTimeMs() / 1000) * 1000);
}

void Timer::increaseOneHour() {
  this->ignoreMillis();

  unsigned long hours = this->getHours();

  if (hours < 24) {
    hours++;
  } else {
    hours = 0;
  }

  unsigned long newTime =
      hours * 3600000 + this->getMinutes() * 60000 + this->getSeconds() * 1000;

  if (newTime > 86400000) {
    newTime = 86400000;
  }

  this->setRemainingTimeMs(newTime);
  this->setDurationMs(newTime);
}

void Timer::decreaseOneHour() {
  this->ignoreMillis();

  unsigned long hours = this->getHours();

  if (hours > 0) {
    hours--;
  } else {
    hours = 24;
  }

  unsigned long newTime =
      hours * 3600000 + this->getMinutes() * 60000 + this->getSeconds() * 1000;

  if (newTime > 86400000) {
    newTime = 86400000;
  }

  this->setRemainingTimeMs(newTime);
  this->setDurationMs(newTime);
}

void Timer::increaseOneMinute() {
  this->ignoreMillis();

  unsigned long minutes = this->getMinutes();

  if (minutes < 59) {
    minutes++;
  } else {
    minutes = 0;
  }

  unsigned long newTime =
      this->getHours() * 3600000 + minutes * 60000 + this->getSeconds() * 1000;

  if (newTime > 86400000) {
    newTime = 86400000;
  }

  this->setRemainingTimeMs(newTime);
  this->setDurationMs(newTime);
}

void Timer::decreaseOneMinute() {
  this->ignoreMillis();

  unsigned long minutes = this->getMinutes();

  if (minutes > 0) {
    minutes--;
  } else {
    minutes = 59;
  }

  unsigned long newTime =
      this->getHours() * 3600000 + minutes * 60000 + this->getSeconds() * 1000;

  if (newTime > 86400000) {
    newTime = 86400000;
  }

  this->setRemainingTimeMs(newTime);
  this->setDurationMs(newTime);
}

void Timer::increaseOneSecond() {
  this->ignoreMillis();

  unsigned long seconds = this->getSeconds();

  if (seconds < 59) {
    seconds++;
  } else {
    seconds = 0;
  }

  unsigned long newTime =
      this->getHours() * 3600000 + this->getMinutes() * 60000 + seconds * 1000;

  if (newTime > 86400000) {
    newTime = 86400000;
  }

  this->setRemainingTimeMs(newTime);
  this->setDurationMs(newTime);
}

void Timer::decreaseOneSecond() {
  this->ignoreMillis();

  unsigned long seconds = this->getSeconds();

  if (seconds > 0) {
    seconds--;
  } else {
    seconds = 59;
  }

  unsigned long newTime =
      this->getHours() * 3600000 + this->getMinutes() * 60000 + seconds * 1000;

  if (newTime > 86400000) {
    newTime = 86400000;
  }

  this->setRemainingTimeMs(newTime);
  this->setDurationMs(newTime);
}

void Timer::reset() {
  logging::logger->Info("Resetting timer");

  void (*resetFunc)(void) = 0;
  resetFunc();
}

void Timer::restart() {
  logging::logger->Info("Restarting timer");

  this->getActiveBuzzer()->AlarmClock();

  this->setState(TIMER_STATE_PAUSED);
  this->setRemainingTimeMs(this->getDurationMs());

  this->getModeButton()->RestartTime();
  this->setUpdatedAtMs(millis());
}

void Timer::await() {
  logging::logger->Info("Pausing timer");

  this->getActiveBuzzer()->Beep();

  this->setState(TIMER_STATE_PAUSED);

  this->getModeButton()->RestartTime();
}

void Timer::run() {
  logging::logger->Info(
      "Remaining time: " + String(this->getRemainingTimeMs()) + " ms");

  this->updateRemainingTimeMs();
  this->setState(TIMER_STATE_RUNNING);
}

void Timer::configSeconds() {
  logging::logger->Info("Configuring timer in seconds");

  this->getActiveBuzzer()->Beep();

  this->setState(TIMER_STATE_CONFIG_SECONDS);

  this->getModeButton()->RestartTime();
}

void Timer::configMinutes() {
  logging::logger->Info("Configuring timer in minutes");

  this->getActiveBuzzer()->Beep();

  this->setState(TIMER_STATE_CONFIG_MINUTES);

  this->getModeButton()->RestartTime();
}

void Timer::configHours() {
  logging::logger->Info("Configuring timer in hours");

  this->getActiveBuzzer()->Beep();

  this->setState(TIMER_STATE_CONFIG_HOURS);

  this->getModeButton()->RestartTime();
}

void Timer::fatalError(const char *message) {
  logging::logger->Error(message);

  this->getDisplay()->DisplayError(String(message));

  delay(5000);
  this->reset();
}

Timer::Timer(unsigned long durationMs, buzzers::ActiveBuzzer *activeBuzzer,
             switches::ControlButton *modeButton,
             switches::ControlButton *upButton,
             switches::ControlButton *downButton, displays::OLED_I2C *display)
    : state(TIMER_STATE_PAUSED), durationMs(durationMs),
      remainingTimeMs(durationMs), updatedAtMs(0), activeBuzzer(activeBuzzer),
      modeButton(modeButton), upButton(upButton), downButton(downButton),
      display(display) {}

Timer::~Timer() {}

void Timer::Do() {
  switches::ControlButtonStatus modeButtonStatus =
      this->getModeButton()->GetStatus();

  TimerState timerState = this->getState();

  logging::logger->Info("Current timer state: " + String(timerState));
  logging::logger->Info("Current control button state: " +
                        String(modeButtonStatus));

  switch (timerState) {
  case TIMER_STATE_PAUSED:
    switch (modeButtonStatus) {
    case switches::CONTROL_BUTTON_PRESSED:
      this->setUpdatedAtMs(millis());
      this->run();
      break;

    case switches::CONTROL_BUTTON_HELD:
      this->configSeconds();
      break;

    default:
      logging::logger->Debug("Control button not handled: Timer still paused");
    }

    break;

  case TIMER_STATE_RUNNING:
    if (this->getRemainingTimeMs() == 0) {
      this->getDisplay()->DisplayTimesUp();
      this->restart();
    }

    switch (modeButtonStatus) {
    case switches::CONTROL_BUTTON_PRESSED:
      this->await();
      break;

    case switches::CONTROL_BUTTON_HELD:
      this->await();
      break;

    default:
      this->run();
    }

    break;

  case TIMER_STATE_CONFIG_SECONDS:
    switch (modeButtonStatus) {
    case switches::CONTROL_BUTTON_PRESSED:
      this->configMinutes();
      break;

    case switches::CONTROL_BUTTON_HELD:
      this->await();
      break;

    default:
      logging::logger->Debug("Control button state not handled");
    }

    break;

  case TIMER_STATE_CONFIG_MINUTES:
    switch (modeButtonStatus) {
    case switches::CONTROL_BUTTON_PRESSED:
      this->configHours();
      break;

    case switches::CONTROL_BUTTON_HELD:
      this->await();
      break;

    default:
      logging::logger->Debug("Control button state not handled");
    }

    break;

  case TIMER_STATE_CONFIG_HOURS:
    switch (modeButtonStatus) {
    case switches::CONTROL_BUTTON_PRESSED:
      this->configSeconds();
      break;

    case switches::CONTROL_BUTTON_HELD:
      this->await();
      break;

    default:
      logging::logger->Debug("Control button state not handled");
    }

    break;

  default:
    this->fatalError("Unknown timer state");
  }

  if (this->getRemainingTimeMs() == 0) {
    this->getDisplay()->DisplayTimesUp();
    this->restart();
  } else {
    this->getDisplay()->DisplayTime(this->getStateString(), this->getHours(),
                                    this->getMinutes(), this->getSeconds());
  }
}

} // namespace controllers