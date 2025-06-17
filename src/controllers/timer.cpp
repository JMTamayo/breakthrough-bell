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
  case TIMER_STATE_CONFIG_HOURS:
    return "Config: Hours";
  case TIMER_STATE_CONFIG_MINUTES:
    return "Config: Minutes";
  case TIMER_STATE_CONFIG_SECONDS:
    return "Config: Seconds";
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

switches::PushSwitch *Timer::getRunPushSwitch() const {
  return this->runPushSwitch;
}

switches::PushSwitch *Timer::getModePushSwitch() const {
  return this->modePushSwitch;
}

switches::PushSwitch *Timer::getUpPushSwitch() const {
  return this->upPushSwitch;
}

switches::PushSwitch *Timer::getDownPushSwitch() const {
  return this->downPushSwitch;
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

  delay(100);
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

  delay(100);
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

  delay(100);
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

  delay(100);
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

  delay(100);
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

  delay(100);
}

void Timer::reset() {
  logging::logger->Info("Resetting timer");

  void (*resetFunc)(void) = 0;
  resetFunc();
}

void Timer::restart() {
  logging::logger->Info("Restarting timer");

  this->setRemainingTimeMs(this->getDurationMs());

  this->getActiveBuzzer()->AlarmClock();

  this->setState(TIMER_STATE_PAUSED);
}

void Timer::await() {
  logging::logger->Info("Pausing timer");

  this->setState(TIMER_STATE_PAUSED);
}

void Timer::run() {
  logging::logger->Info(
      "Remaining time: " + String(this->getRemainingTimeMs()) + " ms");

  this->updateRemainingTimeMs();
  this->setState(TIMER_STATE_RUNNING);
}

void Timer::configSeconds() {
  this->setState(TIMER_STATE_CONFIG_SECONDS);
  this->getActiveBuzzer()->Beep();
  delay(100);
}

void Timer::configMinutes() {
  this->setState(TIMER_STATE_CONFIG_MINUTES);
  this->getActiveBuzzer()->Beep();
  delay(100);
}

void Timer::configHours() {
  this->setState(TIMER_STATE_CONFIG_HOURS);
  this->getActiveBuzzer()->Beep();
  delay(100);
}

void Timer::fatalError(const char *message) {
  logging::logger->Error(message);

  delay(5000);
  this->reset();
}

Timer::Timer(unsigned long durationMs, buzzers::ActiveBuzzer *activeBuzzer,
             switches::PushSwitch *runPushSwitch,
             switches::PushSwitch *modePushSwitch,
             switches::PushSwitch *upPushSwitch,
             switches::PushSwitch *downPushSwitch, displays::OLED_I2C *display)
    : state(TIMER_STATE_PAUSED), durationMs(durationMs),
      remainingTimeMs(durationMs), updatedAtMs(0), activeBuzzer(activeBuzzer),
      runPushSwitch(runPushSwitch), modePushSwitch(modePushSwitch),
      upPushSwitch(upPushSwitch), downPushSwitch(downPushSwitch),
      display(display) {}

Timer::~Timer() {}

void Timer::Do() {
  TimerState currentState = this->getState();

  logging::logger->Info("Current timer state: " + String(currentState));

  switch (currentState) {
  case TIMER_STATE_PAUSED:
    if (this->getRunPushSwitch()->IsPressed()) {
      this->setUpdatedAtMs(millis());
      this->run();
    } else if (this->getModePushSwitch()->IsPressed()) {
      this->configSeconds();
    }

    break;

  case TIMER_STATE_RUNNING:
    if (this->getModePushSwitch()->IsPressed()) {
      this->await();
      this->getActiveBuzzer()->Beep();

    } else if (this->getRemainingTimeMs() == 0) {
      this->getDisplay()->DisplayTimesUp();
      this->restart();

    } else {
      this->run();
    }

    break;

  case TIMER_STATE_CONFIG_SECONDS:
    if (this->getRunPushSwitch()->IsPressed()) {
      this->setUpdatedAtMs(millis());
      this->run();

    } else if (this->getModePushSwitch()->IsPressed()) {
      this->configMinutes();

    } else if (this->getUpPushSwitch()->IsPressed() &&
               !this->getDownPushSwitch()->IsPressed()) {
      this->increaseOneSecond();

    } else if (this->getDownPushSwitch()->IsPressed() &&
               !this->getUpPushSwitch()->IsPressed()) {
      this->decreaseOneSecond();
    }

    break;

  case TIMER_STATE_CONFIG_MINUTES:
    if (this->getRunPushSwitch()->IsPressed()) {
      this->setUpdatedAtMs(millis());
      this->run();

    } else if (this->getModePushSwitch()->IsPressed()) {
      this->configHours();

    } else if (this->getUpPushSwitch()->IsPressed() &&
               !this->getDownPushSwitch()->IsPressed()) {
      this->increaseOneMinute();

    } else if (this->getDownPushSwitch()->IsPressed() &&
               !this->getUpPushSwitch()->IsPressed()) {
      this->decreaseOneMinute();
    }

    break;

  case TIMER_STATE_CONFIG_HOURS:
    if (this->getRunPushSwitch()->IsPressed()) {
      this->setUpdatedAtMs(millis());
      this->run();

    } else if (this->getModePushSwitch()->IsPressed()) {
      this->configSeconds();

    } else if (this->getUpPushSwitch()->IsPressed() &&
               !this->getDownPushSwitch()->IsPressed()) {
      this->increaseOneHour();

    } else if (this->getDownPushSwitch()->IsPressed() &&
               !this->getUpPushSwitch()->IsPressed()) {
      this->decreaseOneHour();
    }

    break;

  default:
    this->fatalError("Timer state not supported");

    break;
  }

  this->getDisplay()->DisplayTime(this->getStateString(), this->getHours(),
                                  this->getMinutes(), this->getSeconds());
}

} // namespace controllers