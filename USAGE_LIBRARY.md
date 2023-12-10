# Arduino Multi-Tasking Kit | Usage > Library

## Interval

Run in regular interval.

### Constructor `Interval(unsigned long time = 0, unsigned int count = 0)`

If `time` has a value, the interval will start _on setup_.

**Parameters**:

- `time`: interval time in milliseconds.
- `count`: number of times to run, 0 for infinite.

### `Interval Interval.setIntervalTime(unsigned long time)`

Set interval time in milliseconds.

**Parameters**:

- `time`: interval time in milliseconds.

**Returns**: `Interval` instance.

### `Interval Interval.start(unsigned long duration = 0, unsigned int count = NULL)`

Start interval.

**Parameters**:

- `duration`: interval duration in milliseconds. `0` for infinite.
- `count`: number of times to run, `NULL` for infinite.

**Returns**: `Interval` instance.

### `Interval Interval.stop()`

Stop interval.

**Returns**: `Interval` instance.

### `bool Interval.onStep()`

Returns `true` on each interval step.

**Returns**: `bool`.

### `bool Interval.isRunning()`

Returns `true` if interval is running.

> Equivalent to `!isFinished()`.

**Returns**: `bool`.

### `bool Interval.isFinished()`

Returns `true` if interval is finished.

> Equivalent to `!isRunning()`.

**Returns**: `bool`.

## Timer

Run only once until time is reached.

### Interval usage example

```c++
#include <Lib_Interval.h>
#include <Component_Button.h>

Interval interval(500);
Button btn(3);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();

  if (interval.onStep()) {
    // On interval step
  }

  if (btn.onClick()) {
    if (interval.isRunning()) {
      interval.stop();
    } else {
      interval.start();
    }
  }
}
```

### Constructor `Timer(unsigned long time = 0)`

If `time` has a value, the timer will start _on setup_.

### `Timer Timer.set(unsigned long time)`

Set timer time.

**Parameters**:

- `time`: timer time in milliseconds.

**Returns**: `Timer` instance.

### `Timer Timer.add(unsigned long time)`

Add time to timer time.

**Parameters**:

- `time`: time to add in milliseconds.

**Returns**: `Timer` instance.

### `Timer Timer.start(unsigned long time = 0)`

When timer time is reached, [`onFinish`](#bool-timeronfinish) will returns true.

**Parameters**:

- `time`: timer time in milliseconds.

**Returns**: `Timer` instance.

### `Timer Timer.stop()`

Stop working timer without running [`onFinish`](#bool-timeronfinish).

**Returns**: `Timer` instance.

### `bool Timer.onDone()`

Returns true only once when the time is reached or wait canceled.

**Returns**: `bool`.

### `bool Timer.onFinish()`

Returns true only once when the time is reached.

**Returns**: `bool`.

### `bool Timer.isRunning()`

Returns true when timer is waiting.

**Returns**: `bool`.

### `bool Timer.isFinished()`

Returns true when timer is not waiting.

**Returns**: `bool`.

### Timer usage example

```c++
#include <Lib_Timer.h>
#include <Component_Button.h>

Timer timer(5000);
Button btn(2);

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();

  if (timer.onFinish()) {
    // On timer finish, run once
  }

  if (timer.isFinished()) {
    // On timer is finished, run every cycle
  } else {
    // On timer is running, run every cycle
  }

  if (btn.onClick()) {
    timer.start();
  }
}
```

## While

While loop without blocking the main loop.

### `bool While.on(unsigned long time, bool condition = true)`

On each `while` step.

**Parameters**:

- `time`: time to wait in milliseconds.
- `condition`: condition to run the `while` loop.

**Returns**: `true` when the code should be executed.

### While usage example

```c++
#include <Lib_While.h>

While whileTest;
While whileTestCondition;
bool foo = false;

void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();

  if (whileTest.on(1000)) {
    // Run every 1000ms
  }

  if (whileTestCondition.on(500, foo)) {
    // Run every 1000ms when `foo` is true
  }

  // The rest of the code...
}
```
