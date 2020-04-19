#include "Lib_Timer.h"

Timer::Timer(unsigned long time = 0) :
  _time(time)
{}

void Timer::setup() {
  this->_autoStart = this->_time > 0;
}

void Timer::loop() {
  if (this->_autoStart) {
    this->_autoStart = false;
    this->start();
  }

  if (this->_start > 0) {
    unsigned long current = millis();
    unsigned long to = this->_start + this->_time;

    if (current >= to) {
      this->_start = 0;
      this->_done = true;

    }
  }
}

Timer* Timer::set(unsigned long time) {
  this->_time = time;
  return this;
}

Timer* Timer::add(unsigned long time) {
  this->_time += time;
  return this;
}

Timer* Timer::start() {
  this->_start = millis();
  this->_done = false;
  return this;
}

Timer* Timer::reset() {
  return this->start();
}

Timer* Timer::stop() {
  this->_start = 0;
  this->_done = false;
  return this;
}

bool Timer::onFinish() {
  const bool d = this->_done;

  if (d) {
  }

  this->_done = false;
  return d;
}

bool Timer::isFinished() {
  return this->_start == 0;
}
