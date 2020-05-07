#ifndef LIB_COMPONENT_LED_DISPLAY8
#define LIB_COMPONENT_LED_DISPLAY8

#include "App_Runnable.h"
#include "Component_PinOutDigital.h"

/**
 * Control 8-Segments Led Display.
 *
 * @note Connection:
 *  [LD8+ | LD8-3 | LD8-8] <> (+)
 *  [LD8-1] <> pin1
 *  [LD8-2] <> pin2
 *  [LD8-4] <> pin3
 *  [LD8-5] <> pin4
 *  [LD8-6] <> pin5
 *  [LD8-7] <> pin6
 *  [LD8-9] <> pin7
 *  [LD8-10] <> pin8_dot
 */
class LedDisplay8: public Runnable {
  private:
    PinOutDigital _pin1;
    PinOutDigital _pin2;
    PinOutDigital _pin3;
    PinOutDigital _pin4;
    PinOutDigital _pin5;
    PinOutDigital _pin6;
    PinOutDigital _pin7;
    PinOutDigital _pin8_dot;

  protected:
    void onSetup() {
      this->off();
    }

  public:

    /**
     * @param pin1 Number segment 1 led pin.
     * @param pin2 Number segment 2 led pin.
     * @param pin3 Number segment 3 led pin.
     * @param pin4 Number segment 4 led pin.
     * @param pin5 Number segment 5 led pin.
     * @param pin6 Number segment 6 led pin.
     * @param pin7 Number segment 7 led pin.
     * @param pin8_dot Dot output pin.
     */
    LedDisplay8(
      uint8_t pin1,
      uint8_t pin2,
      uint8_t pin3,
      uint8_t pin4,
      uint8_t pin5,
      uint8_t pin6,
      uint8_t pin7,
      uint8_t pin8_dot
    ) :
      _pin1(pin1),
      _pin2(pin2),
      _pin3(pin3),
      _pin4(pin4),
      _pin5(pin5),
      _pin6(pin6),
      _pin7(pin7),
      _pin8_dot(pin8_dot)
    { }

    /**
     * Turn off all leds.
     *
     * @return This instance.
     */
    LedDisplay8* off() {
      this->_pin1.on();
      this->_pin2.on();
      this->_pin3.on();
      this->_pin4.on();
      this->_pin5.on();
      this->_pin6.on();
      this->_pin7.on();
      return this->setPoint(false);
    }

    /**
     * Set point state.
     *
     * @param status Point status. True to turn it on, False to turn it off.
     * @return This instance.
     */
    LedDisplay8* setPoint(bool point) {
      if (point) {
        // Point on
        this->_pin8_dot.off();
      } else {
        // Point off
        this->_pin8_dot.on();
      }

      return this;
    }

    /**
     * Set display number.
     *
     * @param n Number to display.
     * @param point Point status. True to turn it on, False to turn it off.
     * @return This instance.
     */
    LedDisplay8* set(uint8_t n, bool point = false) {
      this->setPoint(point);

      switch (n) {
        case 0:
          this->_pin1.on();
          this->_pin2.off();
          this->_pin3.off();
          this->_pin4.off();
          this->_pin5.off();
          this->_pin6.off();
          this->_pin7.off();
          break;
        case 1:
          this->_pin1.on();
          this->_pin2.on();
          this->_pin3.on();
          this->_pin4.off();
          this->_pin5.on();
          this->_pin6.on();
          this->_pin7.off();
          break;
        case 2:
          this->_pin1.off();
          this->_pin2.on();
          this->_pin3.off();
          this->_pin4.off();
          this->_pin5.off();
          this->_pin6.off();
          this->_pin7.on();
          break;
        case 3:
          this->_pin1.off();
          this->_pin2.on();
          this->_pin3.off();
          this->_pin4.off();
          this->_pin5.on();
          this->_pin6.off();
          this->_pin7.off();
          break;
        case 4:
          this->_pin1.off();
          this->_pin2.off();
          this->_pin3.on();
          this->_pin4.off();
          this->_pin5.on();
          this->_pin6.on();
          this->_pin7.off();
          break;
        case 5:
          this->_pin1.off();
          this->_pin2.off();
          this->_pin3.off();
          this->_pin4.on();
          this->_pin5.on();
          this->_pin6.off();
          this->_pin7.off();
          break;
        case 6:
          this->_pin1.off();
          this->_pin2.on();
          this->_pin3.off();
          this->_pin4.off();
          this->_pin5.off();
          this->_pin6.off();
          this->_pin7.off();
          break;
        case 7:
          this->_pin1.on();
          this->_pin2.on();
          this->_pin3.off();
          this->_pin4.off();
          this->_pin5.on();
          this->_pin6.on();
          this->_pin7.off();
          break;
        case 8:
          this->_pin1.off();
          this->_pin2.off();
          this->_pin3.off();
          this->_pin4.off();
          this->_pin5.off();
          this->_pin6.off();
          this->_pin7.off();
          break;
        case 9:
          this->_pin1.off();
          this->_pin2.off();
          this->_pin3.off();
          this->_pin4.off();
          this->_pin5.on();
          this->_pin6.on();
          this->_pin7.off();
          break;
        default:
          // Invalid!
          this->off();
          // Point on
          this->setPoint(true);
          break;
      }

      return this;
    }
};

#endif
