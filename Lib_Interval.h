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
    unsigned long _time = 0;
    unsigned long _start = 0;

  protected:
    void setup();
    void loop();

  public:
    /**
     * Create an interval.
     * If @time has a value, the interval will start on @setup.
     *
     * @param time Time in milliseconds.
     */
    Interval(unsigned long time = 0);

    /**
     * Set interval time.
     *
     * @param time Time in milliseconds.
     * @return This instance.
     */
    Interval* set(unsigned long time);

    /**
     * Start interval.
     * When interval time is reached, @onStep will returns true.
     *
     * @param time Time in milliseconds. 0 to ignore @set.
     * @return This instance.
     * @see stop
     * @see onStep
     */
    Interval* start(unsigned long time = 0);

    /**
     * Stop working interval without running @onStep.
     *
     * @return This instance.
     * @see start
     * @see onStep
     */
    Interval* stop();

    /**
     * Returns true only once each interval.
     *
     * @return True on time reached.
     * @see start
     * @see stop
     * @see isRunning
     */
    bool onStep();

    /**
     * Returns true when interval is running.
     *
     * @return True on interval is running.
     */
    bool isRunning();
};

#endif
