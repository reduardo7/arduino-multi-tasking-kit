#ifndef LIB_TIMER
#define LIB_TIMER

#include "App_Runnable.h"

/**
 * Timer.
 */
class Timer: public Runnable {
  private:
    bool _autoStart = false;
    bool _done = false;
    unsigned long _time = 0;
    unsigned long _start = 0;

  protected:
    void setup() {
      this->_autoStart = this->_time > 0;
    }

    void loop() {
      if (this->_autoStart) {
        this->_autoStart = false;
        this->start();
      }

      if (this->_start > 0 && this->_time) {
        unsigned long current = millis();
        unsigned long to = this->_start + this->_time;

        if (current >= to) {
          this->_start = 0;
          this->_done = true;

        }
      }
    }

  public:
    /**
     * Create a timer.
     * If @time has a value, the timer will start on @setup.
     *
     * @param time Time in milliseconds.
     */
    Timer(unsigned long time = 0) :
      _time(time)
    {}

    /**
     * Set timer time.
     *
     * @param time Time in milliseconds.
     * @return This instance.
     */
    Timer* set(unsigned long time) {
      this->_time = time;
      return this;
    }

    /**
     * Add time to timer time.
     *
     * @param time Time in milliseconds.
     * @return This instance.
     */
    Timer* add(unsigned long time) {
      this->_time += time;
      return this;
    }

    /**
     * Start timer.
     * When timer time is reached, @onFinish will returns true.
     *
     * @param time Time in milliseconds. 0 to ignore @set.
     * @return This instance.
     * @see set
     * @see stop
     * @see onFinish
     */
    Timer* start(unsigned long time = 0) {
      if (time > 0) {
        this->set(time);
      }

      this->_start = millis();
      this->_done = false;
      return this;
    }

    /**
     * Stop working timer without running @onFinish.
     *
     * @return This instance.
     * @see start
     * @see onFinish
     */
    Timer* stop() {
      this->_start = 0;
      this->_done = false;
      return this;
    }

    /**
     * Returns true only once when the time is reached.
     *
     * @return True on time reached.
     * @see start
     * @see stop
     * @see isFinished
     */
    bool onFinish() {
      const bool d = this->_done;
      this->_done = false;
      return d;
    }

    /**
     * Returns true when timer is not waiting.
     *
     * @return True on timer is not waiting.
     */
    bool isFinished() {
      return this->_start == 0;
    }
};

#endif
