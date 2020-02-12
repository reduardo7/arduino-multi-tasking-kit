#ifndef LIB_COMPONENT_LED_DISPLAY
#define LIB_COMPONENT_LED_DISPLAY

#include <Arduino.h>
#include "App_Runnable.h"
#include "Component_Led.h"

class LedDisplay: public Runnable {
  private:
    const Led _l1;
    const Led _l2;
    const Led _l3;
    const Led _l4;
    const Led _l5;
    const Led _l6;
    const Led _l7;
    const Led _lp;

  public:
    LedDisplay(byte l1, byte l2, byte l3, byte l4, byte l5, byte l6, byte l7, byte lp);
    void setup();
    void loop();
    void off();
    void setPoint(bool point);
    void set(byte n, bool point = false);
};

#endif
