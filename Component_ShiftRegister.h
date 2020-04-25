#ifndef LIB_COMPONENT_SHIFT_REGISTER
#define LIB_COMPONENT_SHIFT_REGISTER

#include "App_Runnable.h"
#include "Utils.h"
#include "Lib_Interval.h"
#include "Component_PinOutDigital.h"

/**
 * Control Pin Out Digital pin shift register.
 */
class ShiftRegister: public Runnable {
  private:
    const unsigned long _loopDuration;
    const unsigned int _loopCount;
    const uint8_t * _pinsRef;
    uint8_t _index = 0;
    uint8_t _total;
    bool _directionNext;
    bool _midStep;
    Interval _interval;
    PinOutDigital ** _pins;

  protected:
    void setup() {
      for (int i = 0; i < this->_total; i++) {
        this->_pins[i] = new PinOutDigital(this->_pinsRef[i]);
      }

      if (this->_loopDuration) {
        this->start(this->_loopDuration, this->_loopCount);
      }
    }

    void loop() {
      if (this->_interval.onStep()) {
        if (this->_midStep) {
          this->move();

          for (int i = 0; i < this->_total; i++) {
            this->_pins[i][0].set(this->_index == i);
          }
        } else {
          for (int i = 0; i < this->_total; i++) {
            this->_pins[i][0].off();
          }

          this->move();
        }
      }
    }

  public:
    /**
     * @param pins Board digital pins references.
     * @param loopDuration Time between loop. 0 to no auto start loop.
     * @param loopCount Repeat times. Set 0 for infinite loop.
     * @param directionNext True to move next, false to move previous.
     * @param midStep Move mid step.
     */
    ShiftRegister(
      uint8_t * pins,
      unsigned long loopDuration = 0,
      unsigned int loopCount = 0,
      bool directionNext = true,
      bool midStep = false
    ):
      _pinsRef(pins),
      _interval(),
      _loopDuration(loopDuration),
      _loopCount(loopCount),
      _directionNext(directionNext),
      _midStep(midStep)
    {
      this->_total = Utils::arrayLen(this->_pinsRef);
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
