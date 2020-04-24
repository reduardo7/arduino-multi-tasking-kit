#ifndef LIB_COMPONENT_PIN_IN_DIGITAL
#define LIB_COMPONENT_PIN_IN_DIGITAL

#include <Arduino.h>
#include "App_Runnable.h"

/**
 * Control Pin In Digital pin.
 *
 * @note Connection:
 *  [R10k] <> (-)
 *  {pin} <> [R10k]
 *  {pin} <SWITCH> (+)
 */
class PinInDigital: public Runnable {
  private:
    const uint8_t _pin;

  protected:
    void setup();
    void loop();

  public:
    /**
     * @param pin Board digital pin reference.
     */
    PinInDigital(uint8_t pin);

    /**
     * Get output state.
     *
     * @return Current output state.
     */
    uint8_t get();

    /**
     * Get if output state is HIGH.
     *
     * @return True if state is HIGH.
     * @see getState
     */
    bool isHigh();
};

#endif
