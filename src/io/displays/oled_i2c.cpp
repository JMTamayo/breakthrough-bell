#include <Arduino.h>
#include <Wire.h>

#include "oled_i2c.h"

namespace displays {

Adafruit_SSD1306 *OLED_I2C::getDisplay() const { return this->display; }

String OLED_I2C::getTimeString(unsigned int hours, unsigned int minutes,
                               unsigned int seconds) {
  String hoursString, minutesString, secondsString, timeString;

  if (hours < 10) {
    hoursString = "0" + String(hours);
  } else {
    hoursString = String(hours);
  }

  if (minutes < 10) {
    minutesString = "0" + String(minutes);
  } else {
    minutesString = String(minutes);
  }

  if (seconds < 10) {
    secondsString = "0" + String(seconds);
  } else {
    secondsString = String(seconds);
  }

  timeString = hoursString + ":" + minutesString + ":" + secondsString;

  return timeString;
}

OLED_I2C::OLED_I2C(unsigned int width, unsigned int height, int resetPin,
                   unsigned int address) {
  this->display = new Adafruit_SSD1306(width, height, &Wire, resetPin);

  this->getDisplay()->begin(SSD1306_SWITCHCAPVCC, address);
}

OLED_I2C::~OLED_I2C() {}

void OLED_I2C::HomeScreen() {
  this->getDisplay()->clearDisplay();

  this->getDisplay()->setTextSize(1);
  this->getDisplay()->setTextColor(SSD1306_WHITE);
  this->getDisplay()->setCursor(0, 0);
  this->getDisplay()->println("Breakthrough");

  this->getDisplay()->setTextSize(3);
  this->getDisplay()->setCursor(0, 10);
  this->getDisplay()->println("Bell");

  this->getDisplay()->display();
  delay(3000);
}

void OLED_I2C::DisplayTime(String header, unsigned int hours,
                           unsigned int minutes, unsigned int seconds) {

  this->getDisplay()->clearDisplay();

  this->getDisplay()->setTextSize(1);
  this->getDisplay()->setTextColor(SSD1306_WHITE);
  this->getDisplay()->setCursor(0, 0);
  this->getDisplay()->println(header);

  String timeString = this->getTimeString(hours, minutes, seconds);

  this->getDisplay()->setTextSize(2);
  this->getDisplay()->setTextColor(SSD1306_WHITE);
  this->getDisplay()->setCursor(18, 13);
  this->getDisplay()->println(timeString);

  this->getDisplay()->display();
}

void OLED_I2C::DisplayError(String error) {
  this->getDisplay()->clearDisplay();

  this->getDisplay()->setTextSize(1);
  this->getDisplay()->setTextColor(SSD1306_WHITE);
  this->getDisplay()->setCursor(0, 0);
  this->getDisplay()->println("Error");

  this->getDisplay()->setTextSize(1);
  this->getDisplay()->setCursor(0, 9);
  this->getDisplay()->println(error);

  this->getDisplay()->display();
}

void OLED_I2C::DisplayTimesUp() {
  this->getDisplay()->clearDisplay();

  this->getDisplay()->setTextSize(2);
  this->getDisplay()->setTextColor(SSD1306_WHITE);
  this->getDisplay()->setCursor(8, 9);
  this->getDisplay()->println("Time's Up!");

  this->getDisplay()->display();
}

} // namespace displays