#ifndef LIB_COMPONENT_SHIFT_REGISTER
#define LIB_COMPONENT_SHIFT_REGISTER

#include "App_Runnable.h"
#include "Lib_Interval.h"

/**
 * Control Pin Out Digital pin shift register.
 */
class ShiftRegister: public Runnable {
  private:
    static const uint8_t _PIN_VOID = 31;

    const uint8_t _pin0;
    const uint8_t _pin1;
    const uint8_t _pin2;
    const uint8_t _pin3;
    const uint8_t _pin4;
    const uint8_t _pin5;
    const uint8_t _pin6;
    const uint8_t _pin7;

    uint8_t _total = 0;
    uint8_t _index = 0;
    bool _directionNext;
    // @TODO _midStep
    bool _midStep;
    Interval _interval;

  protected:
    void onSetup() {
      if (this->_pin0 < ShiftRegister::_PIN_VOID) {
        pinMode(this->_pin0, OUTPUT);
        if (this->_pin1 < ShiftRegister::_PIN_VOID) {
          pinMode(this->_pin1, OUTPUT);
          if (this->_pin2 < ShiftRegister::_PIN_VOID) {
            pinMode(this->_pin2, OUTPUT);
            if (this->_pin3 < ShiftRegister::_PIN_VOID) {
              pinMode(this->_pin3, OUTPUT);
              if (this->_pin4 < ShiftRegister::_PIN_VOID) {
                pinMode(this->_pin4, OUTPUT);
                if (this->_pin5 < ShiftRegister::_PIN_VOID) {
                  pinMode(this->_pin5, OUTPUT);
                  if (this->_pin6 < ShiftRegister::_PIN_VOID) {
                    pinMode(this->_pin6, OUTPUT);
                    if (this->_pin7 < ShiftRegister::_PIN_VOID) {
                      pinMode(this->_pin7, OUTPUT);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    void onLoop() {
      if (this->_interval.onStep()) {
        // @TODO _midStep
        // if (this->_midStep) {
        // } else {
        // }
        this->move();
      }
    }

    void onReady() {
      this->exec();
    }

    void exec() {
      if (this->_pin0 < ShiftRegister::_PIN_VOID) {
        digitalWrite(this->_pin0, this->_index == 0 ? HIGH : LOW);
        if (this->_pin1 < ShiftRegister::_PIN_VOID) {
          digitalWrite(this->_pin1, this->_index == 1 ? HIGH : LOW);
          if (this->_pin2 < ShiftRegister::_PIN_VOID) {
            digitalWrite(this->_pin2, this->_index == 2 ? HIGH : LOW);
            if (this->_pin3 < ShiftRegister::_PIN_VOID) {
              digitalWrite(this->_pin3, this->_index == 3 ? HIGH : LOW);
              if (this->_pin4 < ShiftRegister::_PIN_VOID) {
                digitalWrite(this->_pin4, this->_index == 4 ? HIGH : LOW);
                if (this->_pin5 < ShiftRegister::_PIN_VOID) {
                  digitalWrite(this->_pin5, this->_index == 5 ? HIGH : LOW);
                  if (this->_pin6 < ShiftRegister::_PIN_VOID) {
                    digitalWrite(this->_pin6, this->_index == 6 ? HIGH : LOW);
                    if (this->_pin7 < ShiftRegister::_PIN_VOID) {
                      digitalWrite(this->_pin7, this->_index == 7 ? HIGH : LOW);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

  public:
    /**
     * @param pin0 Board digital pin 0 out.
     * @param pin1 Board digital pin 1 out.
     * @param pin2 Board digital pin 2 out.
     * @param pin3 Board digital pin 3 out.
     * @param pin4 Board digital pin 4 out.
     * @param pin5 Board digital pin 5 out.
     * @param pin6 Board digital pin 6 out.
     * @param pin7 Board digital pin 7 out.
     */
    ShiftRegister(
      uint8_t pin0 = ShiftRegister::_PIN_VOID,
      uint8_t pin1 = ShiftRegister::_PIN_VOID,
      uint8_t pin2 = ShiftRegister::_PIN_VOID,
      uint8_t pin3 = ShiftRegister::_PIN_VOID,
      uint8_t pin4 = ShiftRegister::_PIN_VOID,
      uint8_t pin5 = ShiftRegister::_PIN_VOID,
      uint8_t pin6 = ShiftRegister::_PIN_VOID,
      uint8_t pin7 = ShiftRegister::_PIN_VOID
    ):
      _pin0(pin0),
      _pin1(pin1),
      _pin2(pin2),
      _pin3(pin3),
      _pin4(pin4),
      _pin5(pin5),
      _pin6(pin6),
      _pin7(pin7),
      _interval()
    {
      if (pin0 < ShiftRegister::_PIN_VOID) {
        _total++;
        if (pin1 < ShiftRegister::_PIN_VOID) {
          _total++;
          if (pin2 < ShiftRegister::_PIN_VOID) {
            _total++;
            if (pin3 < ShiftRegister::_PIN_VOID) {
              _total++;
              if (pin4 < ShiftRegister::_PIN_VOID) {
                _total++;
                if (pin5 < ShiftRegister::_PIN_VOID) {
                  _total++;
                  if (pin6 < ShiftRegister::_PIN_VOID) {
                    _total++;
                    if (pin7 < ShiftRegister::_PIN_VOID) {
                      _total++;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    /**
     * Set loop direction.
     *
     * @param directionNext True to move next, false to move previous.
     * @return This instance.
     * @see move
     * @see invertDirection
     */
    ShiftRegister* setDirectionNext(bool directionNext) {
      this->_directionNext = directionNext;
      return this;
    }

    /**
     * Invert loop direction.
     *
     * @return This instance.
     * @see move
     * @see setDirectionNext
     */
    ShiftRegister* invertDirection() {
      this->_directionNext = !this->_directionNext;
      return this;
    }

    /**
     * Set middle step.
     *
     * @param midStep Middle step status.
     * @return This instance.
     */
    ShiftRegister* setMidStep(bool midStep) {
      // @TODO _midStep
      this->_midStep = midStep;
      return this;
    }

    /**
     * Move to previous pin.
     *
     * @return This instance.
     * @see next
     * @see move
     */
    ShiftRegister* prev() {
      if (this->isFirst()) {
        this->_index = this->_total - 1;
      } else {
        this->_index--;
      }

      this->exec();
      return this;
    }

    /**
     * Move to next pin.
     *
     * @return This instance.
     * @see prev
     * @see move
     */
    ShiftRegister* next() {
      if (this->isLast()) {
        this->_index = 0;
      } else {
        this->_index++;
      }

      this->exec();
      return this;
    }

    /**
     * Move @next or @prev.
     *
     * @return This instance.
     * @see next
     * @see prev
     * @see setDirectionNext
     */
    ShiftRegister* move() {
      if (this->_directionNext) {
        this->next();
      } else {
        this->prev();
      }

      return this;
    }

    /**
     * Set index position.
     *
     * @param index Index position.
     * @return This instance.
     * @see next
     * @see prev
     * @see index
     */
    ShiftRegister* setIndex(uint8_t index) {
      if (index < 0) {
        this->_index = 0;
      } else {
        uint8_t t = this->_total - 1;
        if (index > t) {
          this->_index = t;
        } else {
          this->_index = index;
        }
      }

      return this;
    }

    /**
     * Is it the last pin?
     *
     * @return True if it is the last pin.
     */
    bool isLast() {
      return this->_index + 1 == this->_total;
    }

    /**
     * Is it the first pin?
     *
     * @return True if it is the first pin.
     */
    bool isFirst() {
      return this->_index == 0;
    }

    /**
     * Get index.
     *
     * @return Current index.
     * @see setIndex
     */
    uint8_t index() {
      return this->_index;
    }

    /**
     * Start loop.
     *
     * @param duration Time in milliseconds. 0 to ignore @set.
     * @param count Total times to execute. 0 for infinite loop. NULL to ignore @set.
     * @return This instance.
     * @see stop
     * @see isRunning
     */
    ShiftRegister* start(unsigned long duration = 0, unsigned int count = 0) {
      this->_interval.start(duration, count); // times == 0 : forever
      return this;
    }

    /**
     * Stop loop.
     *
     * @return This instance.
     * @see start
     * @see isRunning
     */
    ShiftRegister* stop() {
      this->_interval.stop();
      return this;
    }

    /**
     * Check if loop is running.
     *
     * @return True if loop is running.
     * @see start
     * @see stop
     */
    bool isRunning() {
      return this->_interval.isRunning();
    }
};

#endif
