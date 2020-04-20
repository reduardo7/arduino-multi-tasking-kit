#include "Lib_Interval.h"

Interval::Interval(unsigned long time = 0, unsigned int count = 0) :
  _time(time),
  _limitCount(count)
{}

void Interval::setup() {
  if (this->_time > 0) {
    this->_working = true;
  }
}

void Interval::loop() {
  if (
    this->_working
    && this->_time
    && (
      (this->_limitCount == 0)
      || (this->_limitCount > this->_count)
    )
  ) {
    unsigned long current = millis();
    unsigned long to = this->_start + this->_time;

    if (current >= to) {
      // Interval step
      this->_count++;
      this->_start = current;
      this->_step = true;
    }
  }
}

Interval* Interval::setIntervalTime(unsigned long time) {
  this->_time = time;
  return this;
}

Interval* Interval::setIntervalCount(unsigned int count) {
  this->_limitCount = count;
  return this;
}

Interval* Interval::start(unsigned long duration = 0, unsigned int count = NULL) {
  if (duration > 0) {
    this->setIntervalTime(duration);
  }

  if (count != NULL) {
    this->setIntervalCount(count);
  }

  this->_start = millis();
  this->_count = 0;
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
