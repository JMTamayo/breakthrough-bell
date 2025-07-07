#ifndef SWITCHES_H
#define SWITCHES_H

namespace switches {

class Button {
private:
  const unsigned int pin;

  const unsigned int getPin() const;

public:
  Button(unsigned int pin);

  virtual ~Button();

  bool IsPressed() const;
};

enum ControlButtonStatus {
  CONTROL_BUTTON_NOT_PRESSED = 0,
  CONTROL_BUTTON_PRESSED = 1,
  CONTROL_BUTTON_HELD = 2,
};

class ControlButton : public Button {
private:
  const unsigned long debounceDelayMs;
  const unsigned long heldThresholdMs;
  unsigned long updatedAtMs;

  const unsigned long getDebounceDelayMs() const;

  const unsigned long getHeldThresholdMs() const;

  unsigned long getUpdatedAtMs() const;
  void setStatus(ControlButtonStatus status);

public:
  ControlButton(unsigned int pin, unsigned long debounceDelayMs,
                unsigned long heldThresholdMs);

  ~ControlButton() override;

  void RestartTime();

  ControlButtonStatus GetStatus();
};

} // namespace switches

#endif