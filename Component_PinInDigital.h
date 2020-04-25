#ifndef LIB_COMPONENT_PIN_IN_DIGITAL
#define LIB_COMPONENT_PIN_IN_DIGITAL

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
    void setup() {
      pinMode(this->_pin, INPUT);
    }

    void loop() {}

  public:
    /**
     * @param pin Board digital pin reference.
     */
    PinInDigital(uint8_t pin):
      _pin(pin)
    {}

    /**
     * Get output state.
     *
     * @return Current output state.
     */
    uint8_t get() {
      return digitalRead(this->_pin);
    }

    /**
     * Get if output state is HIGH.
     *
     * @return True if state is HIGH.
     * @see getState
     */
    bool isHigh() {
      return this->get() == HIGH;
    }
};

#endif
