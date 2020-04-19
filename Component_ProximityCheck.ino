#include "Component_ProximityCheck.h"

template <typename T>
unsigned long arrayLen(T *x) {
  return sizeof(x) / sizeof(x[0]);
}

int ProximityCheck::_checkInputState(bool state) {
  this->_led.set(state);
  delay(50);
  return analogRead(this->_apin_in);
}

int ProximityCheck::_calibrateMin() {
  int r = 1000;

  for (int i = 0; i < 3; i++) {
    int x = this->_checkInputState(false);
    if (x < r) r = x;
    delay(1000);
  }

  return r;
}

int ProximityCheck::_calibrateMax() {
  int r = 0;

  for (int i = 0; i < 3; i++) {
    int x = this->_checkInputState(true);
    if (x > r) r = x;
    delay(1000);
  }

  return r;
}

ProximityCheck::ProximityCheck(byte led_pin, byte apin_in) :
  _led(led_pin),
  _apin_in(apin_in)
{
  this->_STEPS_LEN = arrayLen(_STEPS);
}

void ProximityCheck::setup() {}

void ProximityCheck::loop() {
  int i = 0;
  bool result = true;

  while (result && i < this->_STEPS_LEN) {
    bool state = this->_STEPS[i];
    byte x = this->_checkInputState(state);

    if (state) {
      result = x > this->_prox;
    } else {
      result = x < this->_prox;
    }

    if (!result && i == 0) {
      this->_result = ProximityCheckState::ERROR_FIRST_CHECK; // Error: First check is ON
    }

    i++;
  }

  if (result) {
    this->_result = ProximityCheckState::NO_PROXIMITY; // No proximity
  } else {
    this->_result = ProximityCheckState::PROXIMITY; // Proximity
  }
}

ProximityCheckState ProximityCheck::getState() {
  return this->_result;
}

void ProximityCheck::calibrate() {
  int b = this->_calibrateMax();
  int a = this->_calibrateMin();
  this->_prox = a + (b - a) / 2;
}

/*
  # Code Example:

  ProximityCheck pc(2, A0);

  void setup() {
    Runnable::setupAll();
  }

  void loop() {
    Runnable::loopAll();

    if (btn.isClicked()) {
      pc.calibrate();
    } else {
      switch (pc.getState()) {
        case ProximityCheckState::PROXIMITY:
          // ...
          break;
        case ProximityCheckState::NO_PROXIMITY:
          // ...
          break;
        case ProximityCheckState::ERROR_FIRST_CHECK:
          // ...
          break;
      }
    }
  }
*/
