#ifndef LIB_COMPONENT_PROXIMITY_CHECK
#define LIB_COMPONENT_PROXIMITY_CHECK

#include "App_Runnable.h"
#include "Component_PinOutDigital.h"
#include "Utils.h"

/**
 * Proximity Check State.
 *
 * @see ProximityCheck
 */
enum ProximityCheckState {
  NO_PROXIMITY = 0,
  PROXIMITY = 1,
  ERROR_FIRST_CHECK = 2
};

/**
 * @see https://pimylifeup.com/arduino-light-sensor
 * @see ProximityCheckState
 * @note Connection:
 *  {led_pin} <> [Led +]
 *  (-) <> [Led -]
 *  {apin_in} <> [R 10K] <> (-)
 *  {apin_in} <> [Light Sensor A]
 *  [Light Sensor B] <> (+)
 *
 *  Example:
 *    if (btn.isClicked()) {
 *      pc.calibrate();
 *    } else {
 *      switch (pc.getState()) {
 *        case ProximityCheckState::PROXIMITY:
 *          // ...
 *          break;
 *        case ProximityCheckState::NO_PROXIMITY:
 *          // ...
 *          break;
 *        case ProximityCheckState::ERROR_FIRST_CHECK:
 *          // ...
 *          break;
 *      }
 *    }
 *  }
 */
class ProximityCheck: public Runnable {
  private:
    PinOutDigital _led;
    const uint8_t _apin_in;

    // First should be LOW, to check external light
    const bool _STEPS[4] = {
      false, true, false, true
    };

    int _STEPS_LEN;

    ProximityCheckState _result = ProximityCheckState::NO_PROXIMITY;

    int _prox = 800;

    int _checkInputState(bool state) {
      this->_led.set(state);
      delay(50);
      return analogRead(this->_apin_in);
    }

    int _calibrateMin() {
      int r = 1000;

      for (int i = 0; i < 3; i++) {
        int x = this->_checkInputState(false);
        if (x < r) r = x;
        delay(1000);
      }

      return r;
    }

    int _calibrateMax() {
      int r = 0;

      for (int i = 0; i < 3; i++) {
        int x = this->_checkInputState(true);
        if (x > r) r = x;
        delay(1000);
      }

      return r;
    }

  protected:
    void setup() {}

    void loop() {
      int i = 0;
      bool result = true;

      while (result && i < this->_STEPS_LEN) {
        bool state = this->_STEPS[i];
        uint8_t x = this->_checkInputState(state);

        if (state) {
          result = x > this->_prox;
        } else {
          result = x < this->_prox;
        }

        if (!result && i == 0) {
          this->_result = ProximityCheckState::ERROR_FIRST_CHECK; // Error: First check is ON
        }

        i++;
      }

      if (result) {
        this->_result = ProximityCheckState::NO_PROXIMITY; // No proximity
      } else {
        this->_result = ProximityCheckState::PROXIMITY; // Proximity
      }
    }

  public:
    /**
     * @param led_pin Led pin.
     * @param apin_in Light sensor pin.
     */
    ProximityCheck(uint8_t led_pin, uint8_t apin_in) :
      _led(led_pin),
      _apin_in(apin_in)
    {
      this->_STEPS_LEN = Utils::arrayLen(_STEPS);
    }

    /**
     * Get state.
     *
     * @return Sensor state.
     */
    ProximityCheckState getState() {
      return this->_result;
    }

    /**
     * Calibrate sensor.
     *
     * @return This instance.
     */
    ProximityCheck* calibrate() {
      int b = this->_calibrateMax();
      int a = this->_calibrateMin();
      this->_prox = a + (b - a) / 2;
      return this;
    }
};

#endif
