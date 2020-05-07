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
    static bool isReady;

  protected:
    virtual void onSetup() {}
    virtual void onLoop() {}
    virtual void onReady() {}

  public:
    Runnable() {
      nextRunnable = headRunnable;
      headRunnable = this;
    }

    static void setupAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
        r->onSetup();
      }
    }

    static void loopAll() {
      // Wait until `millis()` has a value
      if (millis()) {
        if (isReady) {
          for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
            r->onLoop();
          }
        } else {
          for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
            r->onReady();
          }

          isReady = true;
        }
      }
    }
};

Runnable *Runnable::headRunnable = NULL;
bool Runnable::isReady = false;

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
