#ifndef ACTIVE_BUZZER_H
#define ACTIVE_BUZZER_H

namespace buzzers {

class ActiveBuzzer {
private:
  const unsigned long pin;

  const unsigned long getPin() const;

public:
  ActiveBuzzer(unsigned long pin);

  ~ActiveBuzzer();

  void Beep();

  void AlarmClock();
};

} // namespace buzzers

#endif // ACTIVE_BUZZER_H