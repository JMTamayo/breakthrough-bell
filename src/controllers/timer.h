#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

#include "../io/buzzers/active_buzzer.h"
#include "../io/displays/oled_i2c.h"
#include "../io/switches/push_switch.h"

namespace controllers {

enum TimerState {
  TIMER_STATE_PAUSED = 0,
  TIMER_STATE_RUNNING = 1,
  TIMER_STATE_CONFIG_HOURS = 2,
  TIMER_STATE_CONFIG_MINUTES = 3,
  TIMER_STATE_CONFIG_SECONDS = 4,
};

class Timer {
private:
  TimerState state;

  unsigned long durationMs;
  unsigned long remainingTimeMs;
  unsigned long updatedAtMs;

  buzzers::ActiveBuzzer *activeBuzzer;

  switches::PushSwitch *runPushSwitch;
  switches::PushSwitch *modePushSwitch;
  switches::PushSwitch *upPushSwitch;
  switches::PushSwitch *downPushSwitch;

  displays::OLED_I2C *display;

  TimerState getState() const;

  void setState(TimerState state);

  String getStateString() const;

  unsigned long getDurationMs() const;

  void setDurationMs(unsigned long durationMs);

  unsigned long getRemainingTimeMs() const;

  void setRemainingTimeMs(unsigned long remainingTimeMs);

  void updateRemainingTimeMs();

  unsigned long getUpdatedAtMs() const;

  void setUpdatedAtMs(unsigned long updatedAtMs);

  buzzers::ActiveBuzzer *getActiveBuzzer() const;

  switches::PushSwitch *getRunPushSwitch() const;

  switches::PushSwitch *getModePushSwitch() const;

  switches::PushSwitch *getUpPushSwitch() const;

  switches::PushSwitch *getDownPushSwitch() const;

  displays::OLED_I2C *getDisplay() const;

  unsigned int getHours() const;

  unsigned int getMinutes() const;

  unsigned int getSeconds() const;

  void ignoreMillis();

  void increaseOneHour();

  void decreaseOneHour();

  void increaseOneMinute();

  void decreaseOneMinute();

  void increaseOneSecond();

  void decreaseOneSecond();

  void reset();

  void restart();

  void await();

  void run();

  void configSeconds();

  void configMinutes();

  void configHours();

  void fatalError(const char *message);

public:
  Timer(unsigned long durationMs, buzzers::ActiveBuzzer *activeBuzzer,
        switches::PushSwitch *runPushSwitch,
        switches::PushSwitch *modePushSwitch,
        switches::PushSwitch *upPushSwitch,
        switches::PushSwitch *downPushSwitch, displays::OLED_I2C *display);

  ~Timer();

  void Do();
};

} // namespace controllers

#endif