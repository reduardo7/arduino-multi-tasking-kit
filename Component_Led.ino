#include "Component_Led.h"

Led::Led(byte pin):
  _pin(pin)
{}

void Led::setup() {
  pinMode(this->_pin, OUTPUT);
  this->off();
}

void Led::loop() {
  unsigned long m = millis();

  if (this->isFlashing() && (m - this->_flash_last_time) >= this->_flash_duration) {
    this->invert();
    this->_flash_last_time = m;

    if (this->_flash_times > 0) {
      this->_flash_index++;
    }
  }
}

bool Led::isFlashing() {
  return (this->_flash_times <= 0 && this->_flash_duration > 0) || (this->_flash_index >= 0 && this->_flash_index < this->_flash_times);
}

void Led::on() {
  digitalWrite(this->_pin, HIGH);
}

void Led::off() {
  digitalWrite(this->_pin, LOW);
}

void Led::invert() {
  this->set(!this->getState());
}

void Led::set(bool state) {
  if (state) {
    this->on();
  } else {
    this->off();
  }
}

bool Led::getState() {
  return digitalRead(this->_pin) == HIGH;
}

void Led::flash(unsigned int duration, unsigned int times) {
  this->_flash_duration = duration;
  this->_flash_times = times * 2; // One time on, one time off | times <= 0 : forever
  this->_flash_index = 0;
  this->_flash_last_time = millis();
}

void Led::flashStop() {
  this->_flash_duration = 0;
}

/*
  # Code Example:

  Led ledState(13);
  Led ledErr(12);

  void setup() {
    Runnable::setupAll();
    ledErr.flash(500, 10);
  }

  void loop() {
    Runnable::loopAll();

    ledState.off();
    delay(1000);
    ledState.on();
    delay(1000);
    ledState.invert();
    delay(1000);
  }
*/
