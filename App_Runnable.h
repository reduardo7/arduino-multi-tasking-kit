#ifndef LIB_APP_RUNNABLE_H
#define LIB_APP_RUNNABLE_H

#include <Arduino.h>

class Runnable {
  private:
    static Runnable *headRunnable;
    Runnable *nextRunnable;

  protected:
    virtual void setup();
    virtual void loop();

  public:
    Runnable();
    static void setupAll();
    static void loopAll();
};

#endif
