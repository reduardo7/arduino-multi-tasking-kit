#ifndef LIB_WHILE
#define LIB_WHILE

#include "App_Runnable.h"

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

    bool on(unsigned long time, bool condition = true) {
      if (condition && this->_time >= this->_current) {
        this->_current = this->_time + time;
        return true;
      }

      return false;
    }
};

#endif
