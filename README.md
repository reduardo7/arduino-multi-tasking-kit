# Arduino Multi-Tasking Kit

Arduino Multi-Tasking Kit Library.

## Setup

1. Clone the repo at `Documents/Arduino/libraries/arduino-arduino-multi-tasking-kit`.

   ```bash
   cd Documents/Arduino/libraries
   git clone git@github.com:reduardo7/arduino-multi-tasking-kit.git
   ```

2. Create the Arduino project.
3. At the _Arduino entry point_ file, call `Runnable::setupAll()`
   at beginning of `setup()` and `Runnable::loopAll()` at beginning of `loop()`.
   Example:

   ```c++
   #include "App_Runnable.h"

   void setup() {
     Serial.begin(9600);

     Runnable::setupAll();

     // Your setup code

     Serial.println("Ready");
   }

   void loop() {
     Runnable::loopAll();

     // Your loop code
   }
   ```

## Usage

See [`USAGE.md`](./USAGE.md).

## Usage examples

See [`/examples`](./examples).

## References

- [Arduino the Object Oriented way](https://paulmurraycbr.github.io/ArduinoTheOOWay.html).
