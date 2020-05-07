#ifndef LIB_COMPONENT_PIN_OUT_DIGITAL
#define LIB_COMPONENT_PIN_OUT_DIGITAL

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
    Interval _interval;

  protected:
    void onSetup() {
      pinMode(this->_pin, OUTPUT);
      this->off();
    }

    void onLoop() {
      if (this->_interval.onStep()) {
        this->invert();
      }
    }

  public:
    /**
     * @param pin Board digital pin reference.
     */
    PinOutDigital(uint8_t pin):
      _pin(pin),
      _interval()
    {}

    /**
     * Set output with 1/HIGH.
     *
     * @return This instance.
     */
    PinOutDigital* on() {
      digitalWrite(this->_pin, HIGH);
      return this;
    }

    /**
     * Set output with 0/LOW.
     *
     * @return This instance.
     */
    PinOutDigital* off() {
      digitalWrite(this->_pin, LOW);
      return this;
    }

    /**
     * Invert output state.
     * If output is 0/LOW then set 1/HIGH, else set 0/LOW.
     *
     * @return This instance.
     * @see on
     * @see off
     * @see set
     */
    PinOutDigital* invert() {
      return this->set(!this->get());
    }

    /**
     * Set output state.
     *
     * @param state State to set 1/HIGH or 0/LOW.
     * @return This instance.
     */
    PinOutDigital* set(uint8_t state) {
      if (state == LOW) {
        this->off();
      } else {
        this->on();
      }

      return this;
    }

    /**
     * Set output state.
     *
     * @param state State to set true=HIGH or false=LOW.
     * @return This instance.
     */
    PinOutDigital* set(bool state) {
      if (state) {
        this->on();
      } else {
        this->off();
      }

      return this;
    }

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

    /**
     * Start flashing.
     *
     * @param duration HIGHT and LOW states time in milliseconds.
     * @param times Repeat times. Set 0 to flash forever.
     * @return This instance.
     * @see flashStop
     * @see isFlashing
     */
    PinOutDigital* flash(unsigned long duration, unsigned int times = 0) {
      this->_interval.start(duration, times * 2); // One time on, one time off | times == 0 : forever
      return this->off();
    }

    /**
     * Stop flashing.
     *
     * @return This instance.
     * @see flash
     * @see isFlashing
     */
    PinOutDigital* flashStop() {
      this->_interval.stop();
      return this;
    }

    /**
     * Check if the output is flashing.
     *
     * @return True if is flashing.
     * @see flash
     * @see flashStop
     */
    bool isFlashing() {
      return this->_interval.isRunning();
    }
};

#endif
