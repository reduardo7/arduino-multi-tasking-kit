#include "Component_PinOutDigital.h"

PinOutDigital::PinOutDigital(uint8_t pin):
  _pin(pin)
{}

void PinOutDigital::setup() {
  pinMode(this->_pin, OUTPUT);
  this->off();
}

void PinOutDigital::loop() {
  if (this->isFlashing()) {
    if (this->_flash_times > 0) {
      this->_flash_index++;
    }

    if (this->isFlashing()) { // Check if is the last flash
      unsigned long current = millis();

      if ((current - this->_flash_last_time) >= this->_flash_duration) {
        this->invert();
        this->_flash_last_time = current;
      }
    } else {
      this->off();
    }
  }
}

bool PinOutDigital::isFlashing() {
  return (this->_flash_times <= 0 && this->_flash_duration > 0)
    || (this->_flash_index >= 0 && this->_flash_index < this->_flash_times);
}

void PinOutDigital::on() {
  digitalWrite(this->_pin, HIGH);
}

void PinOutDigital::off() {
  digitalWrite(this->_pin, LOW);
}

void PinOutDigital::invert() {
  this->set(!this->get());
}

void PinOutDigital::set(uint8_t state) {
  if (state == LOW) {
    this->off();
  } else {
    this->on();
  }
}

void PinOutDigital::set(bool state) {
  if (state) {
    this->on();
  } else {
    this->off();
  }
}

uint8_t PinOutDigital::get() {
  return digitalRead(this->_pin);
}

bool PinOutDigital::isHigh() {
  return this->get() == HIGH;
}

void PinOutDigital::flash(unsigned int duration, unsigned int times = 0) {
  this->_flash_duration = duration;
  this->_flash_times = times * 2; // One time on, one time off | times == 0 : forever
  this->_flash_index = 0;
  this->_flash_last_time = millis();
  this->on();
}

void PinOutDigital::flashStop() {
  this->_flash_duration = 0;
}
