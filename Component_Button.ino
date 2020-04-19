#include "Component_Button.h"

Button::Button(byte pin) :
  _pin(pin)
{
  this->_buttonDownMs = 0;
}

void Button::setup() {
  pinMode(this->_pin, INPUT_PULLUP);
  this->_state = HIGH;
  this->_result = ButtonState::NO;
}

void Button::loop() {
  this->_result = ButtonState::NO;
  int prevState = this->_state;
  this->_state = digitalRead(this->_pin);

  if (prevState == HIGH && this->_state == LOW) {
    this->_buttonDownMs = millis();
  } else if (prevState == LOW && this->_state == HIGH) {
    if (millis() - this->_buttonDownMs < 50) {
      // ignore this for debounce
    } else if (millis() - this->_buttonDownMs < 500) {
      // short click
      this->_result = ButtonState::SHORT;
    } else {
      // long click
      this->_result = ButtonState::LONG;
    }

    this->_buttonDownMs = 0;
  }
}

ButtonState Button::getState() {
  return this->_result;
}

bool Button::isClicked() {
  return this->_result != ButtonState::NO;
}

bool Button::isShortClick() {
  return this->_result == ButtonState::SHORT;
}

bool Button::isLongClick() {
  return this->_result == ButtonState::LONG;
}

bool Button::isDown() {
  return this->_buttonDownMs > 0;
}

/*
  # Code Example:

  Button btn(3);

  void setup() {
    Runnable::setupAll();
  }

  void loop() {
    Runnable::loopAll();

    switch (btn.getState()) {
      case ButtonState::NO:
        // ...
        break;
      case ButtonState::SHORT:
        // ...
        break;
      case ButtonState::LONG:
        // ...
        break;
    }

    if (btn.isClicked()) {
      // ...
    }
  }
*/
