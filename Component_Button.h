#ifndef LIB_COMPONENT_BUTTON
#define LIB_COMPONENT_BUTTON

#include <Arduino.h>
#include "App_Runnable.h"

/**
   Button State
   @see Button
*/
enum ButtonState {
  NO = 0,
  SHORT = 1,
  LONG = 2
};

/**
   @see ButtonState
   @connection
    {pin} <> [Switch] <> (-)
*/
class Button: public Runnable {
  private:
    const byte _pin;
    unsigned int _state;
    unsigned long _buttonDownMs;
    ButtonState _result;

  public:
    Button(byte pin);
    void setup();
    void loop();
    ButtonState getState();
    bool isClicked();
    bool isShortClick();
    bool isLongClick();
};

#endif
