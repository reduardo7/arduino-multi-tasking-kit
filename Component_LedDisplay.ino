#include "Component_LedDisplay.h"
#include "Component_Led.h"

LedDisplay::LedDisplay(byte l1, byte l2, byte l3, byte l4, byte l5, byte l6, byte l7, byte lp) :
  _l1(l1),
  _l2(l2),
  _l3(l3),
  _l4(l4),
  _l5(l5),
  _l6(l6),
  _l7(l7),
  _lp(lp)
{ }

void LedDisplay::setup() {
  this->off();
}

void LedDisplay::loop() {}

void LedDisplay::off() {
  this->_l1.on();
  this->_l2.on();
  this->_l3.on();
  this->_l4.on();
  this->_l5.on();
  this->_l6.on();
  this->_l7.on();
  this->setPoint(false);
}

void LedDisplay::setPoint(bool point) {
  if (point) {
    // Point on
    this->_lp.off();
  } else {
    // Point off
    this->_lp.on();
  }
}

void LedDisplay::set(byte n, bool point = false) {
  this->setPoint(point);

  switch (n) {
    case 0:
      this->_l1.on();
      this->_l2.off();
      this->_l3.off();
      this->_l4.off();
      this->_l5.off();
      this->_l6.off();
      this->_l7.off();
      break;
    case 1:
      this->_l1.on();
      this->_l2.on();
      this->_l3.on();
      this->_l4.off();
      this->_l5.on();
      this->_l6.on();
      this->_l7.off();
      break;
    case 2:
      this->_l1.off();
      this->_l2.on();
      this->_l3.off();
      this->_l4.off();
      this->_l5.off();
      this->_l6.off();
      this->_l7.on();
      break;
    case 3:
      this->_l1.off();
      this->_l2.on();
      this->_l3.off();
      this->_l4.off();
      this->_l5.on();
      this->_l6.off();
      this->_l7.off();
      break;
    case 4:
      this->_l1.off();
      this->_l2.off();
      this->_l3.on();
      this->_l4.off();
      this->_l5.on();
      this->_l6.on();
      this->_l7.off();
      break;
    case 5:
      this->_l1.off();
      this->_l2.off();
      this->_l3.off();
      this->_l4.on();
      this->_l5.on();
      this->_l6.off();
      this->_l7.off();
      break;
    case 6:
      this->_l1.off();
      this->_l2.on();
      this->_l3.off();
      this->_l4.off();
      this->_l5.off();
      this->_l6.off();
      this->_l7.off();
      break;
    case 7:
      this->_l1.on();
      this->_l2.on();
      this->_l3.off();
      this->_l4.off();
      this->_l5.on();
      this->_l6.on();
      this->_l7.off();
      break;
    case 8:
      this->_l1.off();
      this->_l2.off();
      this->_l3.off();
      this->_l4.off();
      this->_l5.off();
      this->_l6.off();
      this->_l7.off();
      break;
    case 9:
      this->_l1.off();
      this->_l2.off();
      this->_l3.off();
      this->_l4.off();
      this->_l5.on();
      this->_l6.on();
      this->_l7.off();
      break;
    default:
      // Invalid!
      this->off();
      // Point on
      this->setPoint(true);
      break;
  }
}

/*
  # Code Example:

  LedDisplay disp(11, 10, 9, 8, 7, 6, 5, 4);
  byte num = 0;

  void setup() {
    Runnable::setupAll();
  }

  void loop() {
    Runnable::loopAll();

    if (btnAdd.isClicked()) {
      num++;
    }

    if (btnMin.isClicked()) {
      num--;
    }

    disp.set(num);
  }
*/
