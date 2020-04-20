#include "Component_PinOutDigital.h"

PinOutDigital::PinOutDigital(uint8_t pin):
  _pin(pin),
  _interval()
{}

void PinOutDigital::setup() {
  pinMode(this->_pin, OUTPUT);
  this->off();
}

void PinOutDigital::loop() {
  if (this->_interval.onStep()) {
    this->invert();
  }
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

void PinOutDigital::flash(unsigned long duration, unsigned int times = 0) {
  this->_interval.start(duration, times * 2); // One time on, one time off | times == 0 : forever
  this->off();
}

bool PinOutDigital::isFlashing() {
  return this->_interval.isRunning();
}

void PinOutDigital::flashStop() {
  this->_interval.stop();
}
