#ifndef LEDS_H
#define LEDS_H

namespace leds {

class Led {
private:
  const unsigned long pin;

  const unsigned long getPin() const;

public:
  Led(unsigned long pin);

  ~Led();

  void Toggle();
};

} // namespace leds

#endif // LEDS_H