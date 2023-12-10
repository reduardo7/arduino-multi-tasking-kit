#ifndef LIB_COMPONENT_BUTTON
#define LIB_COMPONENT_BUTTON

#include "App_Runnable.h"

/**
 * Button State.
 */
enum ButtonState {
  NO = 0,
  SHORT = 1,
  LONG = 2
};

/**
 * Simple button control.
 *
 * @see ButtonState
 * @note Connection:
 *  {pin} <> [Button] <> (-)
 */
class Button: public Runnable {
  private:
    const uint8_t _pin;
    int _state;
    unsigned long _buttonDownMs;
    ButtonState _result;

  protected:
    void onSetup() {
      pinMode(this->_pin, INPUT_PULLUP);
      this->_state = HIGH;
      this->_result = ButtonState::NO;
      this->_buttonDownMs = 0;
    }

    void onLoop() {
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

  public:
    /**
     * @param pin Board digital pin reference.
     */
    Button(uint8_t pin) :
      _pin(pin)
    {}

    /**
     * Was the Button pressed?
     *
     * @return True if the button has been pressed.
     * @see onShortClick
     * @see onLongClick
     */
    bool onClick() {
      return this->_result != ButtonState::NO;
    }

    /**
     * Has the button been pressed short?
     *
     * @return True if the button has been pressed short.
     * @see onClick
     * @see onLongClick
     */
    bool onShortClick() {
      return this->_result == ButtonState::SHORT;
    }

    /**
     * Has the button been pressed long?
     *
     * @return True if the button has been pressed long.
     * @see onClick
     * @see onShortClick
     */
    bool Button::onLongClick() {
      return this->_result == ButtonState::LONG;
    }

    /**
     * Get button state.
     *
     * @return Button state.
     */
    ButtonState getState() {
      return this->_result;
    }

    /**
     * Is the button being pressed?
     *
     * @return True while the button is being pressed.
     */
    bool isPressed() {
      return this->_buttonDownMs > 0;
    }

    /**
     * Is the button being released?
     *
     * @return True while the button is being pressed.
     */
    bool isReleased() {
      return this->_buttonDownMs == 0;
    }
};

#endif
