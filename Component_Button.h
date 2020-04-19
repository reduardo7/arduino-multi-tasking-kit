#ifndef LIB_COMPONENT_BUTTON
#define LIB_COMPONENT_BUTTON

#include <Arduino.h>
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
 *  {pin} <> [Button Pin A]
 *  [Button Pin B] <> (-)
*/
class Button: public Runnable {
  private:
    const uint8_t _pin;
    unsigned int _state;
    unsigned long _buttonDownMs;
    ButtonState _result;

  protected:
    void setup();
    void loop();

  public:
    /**
     * @param pin Board digital pin reference.
     */
    Button(uint8_t pin);

    /**
     * Was the Button pressed?
     *
     * @return True if the button has been pressed.
     * @see isShortClick
     * @see isLongClick
     */
    bool isClicked();

    /**
     * Has the button been pressed short?
     *
     * @return True if the button has been pressed short.
     * @see isClicked
     * @see isLongClick
     */
    bool isShortClick();

    /**
     * Has the button been pressed long?
     *
     * @return True if the button has been pressed long.
     * @see isClicked
     * @see isShortClick
     */
    bool isLongClick();

    /**
     * Is the button being pressed?
     *
     * @return True while the button is being pressed.
     */
    bool isDown();
};

#endif
