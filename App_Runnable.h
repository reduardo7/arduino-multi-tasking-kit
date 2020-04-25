#ifndef LIB_APP_RUNNABLE_H
#define LIB_APP_RUNNABLE_H

#include <Arduino.h>

/**
 * @see http://paulmurraycbr.github.io/ArduinoTheOOWay.html
 */
class Runnable {
  private:
    static Runnable *headRunnable;
    Runnable *nextRunnable;

  protected:
    virtual void setup();
    virtual void loop();

  public:
    Runnable() {
      nextRunnable = headRunnable;
      headRunnable = this;
    }

    static void setupAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
        r->setup();
      }
    }

    static void loopAll() {
      unsigned long current = millis();

      // Wait until `millis()` has a value
      if (current) {
        for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
          r->loop();
        }
      }
    }
};

Runnable *Runnable::headRunnable = NULL;

#endif

/*
  # Code Example:

  void setup() {
    Runnable::setupAll();
  }

  void loop() {
    Runnable::loopAll();
  }
*/
