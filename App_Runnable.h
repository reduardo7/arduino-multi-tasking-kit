#ifndef LIB_APP_RUNNABLE_H
#define LIB_APP_RUNNABLE_H

class Runnable {
  private:
    static Runnable *headRunnable;
    Runnable *nextRunnable;

  public:
    Runnable();
    virtual void setup();
    virtual void loop();
    static void setupAll();
    static void loopAll();
};

#endif
