#ifndef ACTIVE_BUZZER_H
#define ACTIVE_BUZZER_H

namespace buzzers {

class ActiveBuzzer {
private:
  const unsigned int pin;

  const unsigned int getPin() const;

public:
  ActiveBuzzer(unsigned int pin);

  ~ActiveBuzzer();

  void Beep();

  void AlarmClock();
};

} // namespace buzzers

#endif // ACTIVE_BUZZER_H