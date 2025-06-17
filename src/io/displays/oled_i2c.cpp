#include <Arduino.h>
#include <Wire.h>

#include "oled_i2c.h"

namespace displays {

String OLED_I2C::GetTimeString(unsigned int hours, unsigned int minutes,
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

  this->display->begin(SSD1306_SWITCHCAPVCC, address);
}

OLED_I2C::~OLED_I2C() {}

void OLED_I2C::MainScreen() {
  this->display->clearDisplay();

  this->display->setTextSize(1);
  this->display->setTextColor(SSD1306_WHITE);
  this->display->setCursor(0, 0);
  this->display->println("Breakthrough");

  this->display->setTextSize(2);
  this->display->setCursor(0, 10);
  this->display->println("Bell");

  this->display->setTextSize(1);
  this->display->setCursor(62, 24);
  this->display->println("by JMTamayo");

  this->display->display();
}

void OLED_I2C::DisplayTime(String header, unsigned int hours,
                           unsigned int minutes, unsigned int seconds) {

  this->display->clearDisplay();

  this->display->setTextSize(1);
  this->display->setTextColor(SSD1306_WHITE);
  this->display->setCursor(0, 0);
  this->display->println(header);

  String timeString = this->GetTimeString(hours, minutes, seconds);

  this->display->setTextSize(2);
  this->display->setTextColor(SSD1306_WHITE);
  this->display->setCursor(18, 13);
  this->display->println(timeString);

  this->display->display();
}

void OLED_I2C::DisplayError(String error) {
  this->display->clearDisplay();

  this->display->setTextSize(1);
  this->display->setTextColor(SSD1306_WHITE);
  this->display->setCursor(0, 0);
  this->display->println("Error");

  this->display->setTextSize(1);
  this->display->setCursor(0, 9);
  this->display->println(error);

  this->display->display();
}

void OLED_I2C::DisplayTimesUp() {
  this->display->clearDisplay();

  this->display->setTextSize(2);
  this->display->setTextColor(SSD1306_WHITE);
  this->display->setCursor(8, 9);
  this->display->println("Time's Up!");

  this->display->display();
}

} // namespace displays