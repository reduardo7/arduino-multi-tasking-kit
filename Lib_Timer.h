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
    void setup();
    void loop();

  public:
    /**
     * Create a timer.
     * If @time has a value, the timer will start on @setup.
     *
     * @param time Time in milliseconds.
     */
    Timer(unsigned long time = 0);

    /**
     * Set timer time.
     *
     * @param time Time in milliseconds.
     * @return This instance.
     */
    Timer* set(unsigned long time);

    /**
     * Add time to timer time.
     *
     * @param time Time in milliseconds.
     * @return This instance.
     */
    Timer* add(unsigned long time);

    /**
     * Start timer.
     * When timer time is reached, @onFinish will returns true.
     *
     * @return This instance.
     * @see reset
     * @see stop
     * @see onFinish
     */
    Timer* start();

    /**
     * Alias of @start.
     *
     * @return This instance.
     * @see start
     */
    Timer* reset();

    /**
     * Stop working timer without running @onFinish.
     *
     * @return This instance.
     * @see start
     * @see onFinish
     */
    Timer* stop();

    /**
     * Returns true only once when the time is reached.
     *
     * @return True on time reached.
     */
    bool onFinish();

    /**
     * Returns true when timer is not waiting.
     *
     * @return True on timer is not waiting.
     */
    bool isFinished();
};

#endif
