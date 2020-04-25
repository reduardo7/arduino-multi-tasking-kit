#include "Component_LedDisplay8.h"

LedDisplay8::LedDisplay8(
  uint8_t pin1,
  uint8_t pin2,
  uint8_t pin3,
  uint8_t pin4,
  uint8_t pin5,
  uint8_t pin6,
  uint8_t pin7,
  uint8_t pin8_dot
) :
  _pin1(pin1),
  _pin2(pin2),
  _pin3(pin3),
  _pin4(pin4),
  _pin5(pin5),
  _pin6(pin6),
  _pin7(pin7),
  _pin8_dot(pin8_dot)
{ }

void LedDisplay8::setup() {
  this->off();
}

void LedDisplay8::loop() {}

LedDisplay8* LedDisplay8::off() {
  this->_pin1.on();
  this->_pin2.on();
  this->_pin3.on();
  this->_pin4.on();
  this->_pin5.on();
  this->_pin6.on();
  this->_pin7.on();
  return this->setPoint(false);
}

LedDisplay8* LedDisplay8::setPoint(bool point) {
  if (point) {
    // Point on
    this->_pin8_dot.off();
  } else {
    // Point off
    this->_pin8_dot.on();
  }

  return this;
}

LedDisplay8* LedDisplay8::set(uint8_t n, bool point = false) {
  this->setPoint(point);

  switch (n) {
    case 0:
      this->_pin1.on();
      this->_pin2.off();
      this->_pin3.off();
      this->_pin4.off();
      this->_pin5.off();
      this->_pin6.off();
      this->_pin7.off();
      break;
    case 1:
      this->_pin1.on();
      this->_pin2.on();
      this->_pin3.on();
      this->_pin4.off();
      this->_pin5.on();
      this->_pin6.on();
      this->_pin7.off();
      break;
    case 2:
      this->_pin1.off();
      this->_pin2.on();
      this->_pin3.off();
      this->_pin4.off();
      this->_pin5.off();
      this->_pin6.off();
      this->_pin7.on();
      break;
    case 3:
      this->_pin1.off();
      this->_pin2.on();
      this->_pin3.off();
      this->_pin4.off();
      this->_pin5.on();
      this->_pin6.off();
      this->_pin7.off();
      break;
    case 4:
      this->_pin1.off();
      this->_pin2.off();
      this->_pin3.on();
      this->_pin4.off();
      this->_pin5.on();
      this->_pin6.on();
      this->_pin7.off();
      break;
    case 5:
      this->_pin1.off();
      this->_pin2.off();
      this->_pin3.off();
      this->_pin4.on();
      this->_pin5.on();
      this->_pin6.off();
      this->_pin7.off();
      break;
    case 6:
      this->_pin1.off();
      this->_pin2.on();
      this->_pin3.off();
      this->_pin4.off();
      this->_pin5.off();
      this->_pin6.off();
      this->_pin7.off();
      break;
    case 7:
      this->_pin1.on();
      this->_pin2.on();
      this->_pin3.off();
      this->_pin4.off();
      this->_pin5.on();
      this->_pin6.on();
      this->_pin7.off();
      break;
    case 8:
      this->_pin1.off();
      this->_pin2.off();
      this->_pin3.off();
      this->_pin4.off();
      this->_pin5.off();
      this->_pin6.off();
      this->_pin7.off();
      break;
    case 9:
      this->_pin1.off();
      this->_pin2.off();
      this->_pin3.off();
      this->_pin4.off();
      this->_pin5.on();
      this->_pin6.on();
      this->_pin7.off();
      break;
    default:
      // Invalid!
      this->off();
      // Point on
      this->setPoint(true);
      break;
  }

  return this;
}
