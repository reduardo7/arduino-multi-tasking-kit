#include "Component_PinInDigital.h"

PinInDigital::PinInDigital(uint8_t pin):
  _pin(pin)
{}

void PinInDigital::setup() {
  pinMode(this->_pin, INPUT);
}

void PinInDigital::loop() {}

uint8_t PinInDigital::get() {
  return digitalRead(this->_pin);
}

bool PinInDigital::isHigh() {
  return this->get() == HIGH;
}
