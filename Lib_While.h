#ifndef LIB_WHILE
#define LIB_WHILE

#include "App_Runnable.h"

/**
 * While loop without blocking the main loop.
 */
class While: public Runnable {
  private:
    unsigned long _time;
    unsigned long _current;

  protected:
    void onLoop() {
      this->_time = millis();
    }

  public:
    While() {
      this->_current = millis();
    }

    /**
     * On each `while` step.
     *
     * @param time Interval in milliseconds.
     * @param condition Condition to be true.
     */
    bool on(unsigned long time, bool condition = true) {
      if (condition && this->_time >= this->_current) {
        this->_current = this->_time + time;
        return true;
      }

      return false;
    }
};

#endif
