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
    void setup();
    void loop();

  public:
    /**
     * Create an interval.
     * If @time has a value, the interval will start on @setup.
     *
     * @param time Time in milliseconds.
     * @param count Total times to execute. 0 for infinite loop.
     */
    Interval(unsigned long time = 0, unsigned int count = 0);

    /**
     * Set interval time.
     *
     * @param time Time in milliseconds.
     * @return This instance.
     */
    Interval* setIntervalTime(unsigned long time);

    /**
     * Set interval total times to execute.
     *
     * @param time Time in milliseconds. 0 for infinite loop.
     * @return This instance.
     */
    Interval* setIntervalCount(unsigned int count);

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
    Interval* start(unsigned long time = 0, unsigned int count = NULL);

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
