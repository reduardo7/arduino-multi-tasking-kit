#ifndef LIB_COMPONENT_PIN_IN_DIGITAL
#define LIB_COMPONENT_PIN_IN_DIGITAL

#include "App_Runnable.h"

/**
 * Control Pin In Digital pin.
 *
 * @note Connection:
 *  {pin} <> [R10k] <> (-)
 *  {pin} <> [Button / Switch] <> (+)
 */
class PinInDigital: public Runnable {
  private:
    const uint8_t _pin;
    const uint8_t _pinMode;

  protected:
    void onSetup() {
      pinMode(this->_pin, this->_pinMode);
    }

  public:
    /**
     * @param pin Board digital pin reference.
     * @param pullUp Board digital pin mode as INPUT_PULLUP?
     */
    PinInDigital(uint8_t pin, bool pullUp = false):
      _pin(pin),
      _pinMode(pullUp ? INPUT_PULLUP : INPUT)
    {}

    /**
     * Get output state.
     *
     * @return Current output state.
     */
    int get() {
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
