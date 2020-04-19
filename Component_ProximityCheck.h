#ifndef LIB_COMPONENT_PROXIMITY_CHECK
#define LIB_COMPONENT_PROXIMITY_CHECK

#include <Arduino.h>
#include "App_Runnable.h"
#include "Component_PinOutDigital.h"

/**
   Proximity Check State.
   @see ProximityCheck
*/
enum ProximityCheckState {
  NO_PROXIMITY = 0,
  PROXIMITY = 1,
  ERROR_FIRST_CHECK = 2
};

/**
   @see https://pimylifeup.com/arduino-light-sensor
   @see ProximityCheckState
   @connection
    {led_pin} <> [Led +]
    (-) <> [Led -]
    {apin_in} <> [R 10K] <> (-)
    {apin_in} <> [Light Sensor A]
    [Light Sensor B] <> (+)
*/
class ProximityCheck: public Runnable {
  private:
    const PinOutDigital _led;
    const byte _apin_in;

    // First should be LOW, to check external light
    const bool _STEPS[4] = {
      false, true, false, true
    };

    int _STEPS_LEN;

    ProximityCheckState _result = ProximityCheckState::NO_PROXIMITY;

    int _prox = 800;
    int _checkInputState(bool state);
    int _calibrateMin();
    int _calibrateMax();

  protected:
    void setup();
    void loop();

  public:
    ProximityCheck(byte led_pin, byte apin_in);
    ProximityCheckState getState();
    void calibrate();
};

#endif
