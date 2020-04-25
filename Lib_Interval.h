#ifndef LIB_INTERVAL
#define LIB_INTERVAL

#include "App_Runnable.h"

/**
 * Interval.
 */
class Interval: public Runnable {
  private:
    bool _working = false;
    bool _step = false;
    unsigned int _count = 0;
    unsigned int _limitCount = 0;
    unsigned long _time = 0;
    unsigned long _start = 0;

  protected:
    void setup() {
      if (this->_time > 0) {
        this->_working = true;
      }
    }

    void loop() {
      if (
        this->_working
        && this->_time
        && (
          (this->_limitCount == 0)
          || (this->_limitCount > this->_count)
        )
      ) {
        unsigned long current = millis();
        unsigned long to = this->_start + this->_time;

        if (current >= to) {
          // Interval step
          this->_count++;
          this->_start = current;
          this->_step = true;
        }
      }
    }

  public:
    /**
     * Create an interval.
     * If @time has a value, the interval will start on @setup.
     *
     * @param time Time in milliseconds.
     * @param count Total times to execute. 0 for infinite loop.
     */
    Interval(unsigned long time = 0, unsigned int count = 0) :
      _time(time),
      _limitCount(count)
    {}

    /**
     * Set interval time.
     *
     * @param time Time in milliseconds.
     * @return This instance.
     */
    Interval* setIntervalTime(unsigned long time) {
      this->_time = time;
      return this;
    }

    /**
     * Set interval total times to execute.
     *
     * @param time Time in milliseconds. 0 for infinite loop.
     * @return This instance.
     */
    Interval* setIntervalCount(unsigned int count) {
      this->_limitCount = count;
      return this;
    }

    /**
     * Start interval.
     * When interval time is reached, @onStep will returns true.
     *
     * @param time Time in milliseconds. 0 to ignore @set.
     * @param count Total times to execute. 0 for infinite loop. NULL to ignore @set.
     * @return This instance.
     * @see stop
     * @see onStep
     */
    Interval* start(unsigned long duration = 0, unsigned int count = NULL) {
      if (duration > 0) {
        this->setIntervalTime(duration);
      }

      if (count != NULL) {
        this->setIntervalCount(count);
      }

      this->_start = millis();
      this->_count = 0;
      this->_working = true;
      this->_step = false;
      return this;
    }

    /**
     * Stop working interval without running @onStep.
     *
     * @return This instance.
     * @see start
     * @see onStep
     */
    Interval* stop() {
      this->_working = false;
      this->_step = false;
      return this;
    }

    /**
     * Returns true only once each interval.
     *
     * @return True on time reached.
     * @see start
     * @see stop
     * @see isRunning
     */
    bool onStep() {
      const bool s = this->_step;
      this->_step = false;
      return s;
    }

    /**
     * Returns true when interval is running.
     *
     * @return True on interval is running.
     */
    bool isRunning() {
      return this->_working;
    }
};

#endif
