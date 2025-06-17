#ifndef SWITCHES_H
#define SWITCHES_H

namespace switches {

class PushSwitch {
private:
  const unsigned int pin;

  const unsigned int getPin() const;

public:
  PushSwitch(unsigned int pin);

  ~PushSwitch();

  bool IsPressed() const;
};

} // namespace switches

#endif