#ifndef LIB_COMPONENT_PIN_OUT_DIGITAL
#define LIB_COMPONENT_PIN_OUT_DIGITAL

#include <Arduino.h>
#include "App_Runnable.h"
#include "Component_PinOutDigital.h"

/**
   @connection
    {pin} <> [Led +]
    (-) <> [Led -]
*/
class PinOutDigital: public Runnable {
  private:
    const byte _pin;
    unsigned int _flash_duration = -1;
    unsigned int _flash_times = -1;
    unsigned int _flash_index = -1;
    unsigned long _flash_time = 0;
    unsigned long _flash_last_time = 0;

  public:
    PinOutDigital(byte pin);
    void setup();
    void loop();
    bool isFlashing();
    void on();
    void off();
    void invert();
    void set(bool state);
    bool getState();
    void flash(unsigned int duration, unsigned int times);
    void flashStop();
};

#endif
