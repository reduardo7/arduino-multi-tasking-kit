#ifndef LIB_COMPONENT_BUTTON
#define LIB_COMPONENT_BUTTON

#include <Arduino.h>
#include "App_Runnable.h"
#include "Lib_ButtonState.h"

/**
   @see ButtonState
   @connection
    {pin} <> [Switch A]
    [Switch B] <> (-)
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
    bool isDown();
};

#endif
