#include "Lib_Interval.h"

Interval::Interval(unsigned long time = 0) :
  _time(time)
{}

void Interval::setup() {
  if (this->_time > 0) {
    this->_working = true;
  }
}

void Interval::loop() {
  if (this->_working && this->_time) {
    unsigned long current = millis();
    unsigned long to = this->_start + this->_time;

    if (current >= to) {
      this->_start = current;
      this->_step = true;
    }
  }
}

Interval* Interval::set(unsigned long time) {
  this->_time = time;
  return this;
}

Interval* Interval::start(unsigned long time = 0) {
  if (time > 0) {
    this->set(time);
  }

  this->_start = millis();
  this->_working = true;
  this->_step = false;
  return this;
}

Interval* Interval::stop() {
  this->_working = false;
  this->_step = false;
  return this;
}

bool Interval::onStep() {
  const bool s = this->_step;
  this->_step = false;
  return s;
}

bool Interval::isRunning() {
  return this->_working;
}
