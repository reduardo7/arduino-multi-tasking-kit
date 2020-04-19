#ifndef LIB_COMPONENT_LED_DISPLAY8
#define LIB_COMPONENT_LED_DISPLAY8

#include <Arduino.h>
#include "App_Runnable.h"
#include "Component_PinOutDigital.h"

class LedDisplay8: public Runnable {
  private:
    const PinOutDigital _l1;
    const PinOutDigital _l2;
    const PinOutDigital _l3;
    const PinOutDigital _l4;
    const PinOutDigital _l5;
    const PinOutDigital _l6;
    const PinOutDigital _l7;
    const PinOutDigital _lp;

  protected:
    void setup();
    void loop();

  public:
    LedDisplay8(byte l1, byte l2, byte l3, byte l4, byte l5, byte l6, byte l7, byte lp);
    void off();
    void setPoint(bool point);
    void set(byte n, bool point = false);
};

#endif
