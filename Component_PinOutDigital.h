#ifndef LIB_COMPONENT_PIN_OUT_DIGITAL
#define LIB_COMPONENT_PIN_OUT_DIGITAL

#include <Arduino.h>
#include "App_Runnable.h"
#include "Lib_Interval.h"

/**
 * Control Pin Out Digital pin.
 *
 * @note Connection:
 *  {pin} <> [Led +]
 *  (-) <> [Led -]
 */
class PinOutDigital: public Runnable {
  private:
    const uint8_t _pin;
    const Interval _interval;

  protected:
    void setup();
    void loop();

  public:
    /**
     * @param pin Board digital pin reference.
     */
    PinOutDigital(uint8_t pin);

    /**
     * Set output with 1/HIGH.
     * @return This instance.
     */
    PinOutDigital* on();

    /**
     * Set output with 0/LOW.
     * @return This instance.
     */
    PinOutDigital* off();

    /**
     * Invert output state.
     * If output is 0/LOW then set 1/HIGH, else set 0/LOW.
     *
     * @return This instance.
     * @see on
     * @see off
     * @see set
     */
    PinOutDigital* invert();

    /**
     * Set output state.
     *
     * @param state State to set 1/HIGH or 0/LOW.
     * @return This instance.
     */
    PinOutDigital* set(uint8_t state);

    /**
     * Set output state.
     *
     * @param state State to set true=HIGH or false=LOW.
     * @return This instance.
     */
    PinOutDigital* set(bool state);

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

    /**
     * Start flashing.
     *
     * @param duration HIGHT and LOW states time in milliseconds.
     * @param times Repeat times. Set 0 to flash forever.
     * @return This instance.
     * @see flashStop
     * @see isFlashing
     */
    PinOutDigital* flash(unsigned long duration, unsigned int times = 0);

    /**
     * Stop flashing.
     *
     * @return This instance.
     * @see flash
     * @see isFlashing
     */
    PinOutDigital* flashStop();

    /**
     * Check if the output is flashing.
     *
     * @return True if is flashing.
     * @see flash
     * @see flashStop
     */
    bool isFlashing();
};

#endif
