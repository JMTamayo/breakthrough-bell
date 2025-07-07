#ifndef OLED_I2C_H
#define OLED_I2C_H

#include <Arduino.h>

#include <Adafruit_SSD1306.h>

namespace displays {

class OLED_I2C {
private:
  Adafruit_SSD1306 *display;

  String getTimeString(unsigned int hours, unsigned int minutes,
                       unsigned int seconds);

  Adafruit_SSD1306 *getDisplay() const;

public:
  OLED_I2C(unsigned int width, unsigned int height, int resetPin,
           unsigned int address);

  ~OLED_I2C();

  void HomeScreen();

  void DisplayTime(String header, unsigned int hours, unsigned int minutes,
                   unsigned int seconds);

  void DisplayError(String error);

  void DisplayTimesUp();
};

} // namespace displays

#endif // OLED_I2C_H