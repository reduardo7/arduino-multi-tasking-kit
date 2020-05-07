#ifndef LIB_COMPONENT_LED_DISPLAY8
#define LIB_COMPONENT_LED_DISPLAY8

#include "App_Runnable.h"

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
    const uint8_t _pin1;
    const uint8_t _pin2;
    const uint8_t _pin3;
    const uint8_t _pin4;
    const uint8_t _pin5;
    const uint8_t _pin6;
    const uint8_t _pin7;
    const uint8_t _pin8_dot;

  protected:
    void onSetup() {
      pinMode(this->_pin1, OUTPUT);
      pinMode(this->_pin2, OUTPUT);
      pinMode(this->_pin3, OUTPUT);
      pinMode(this->_pin4, OUTPUT);
      pinMode(this->_pin5, OUTPUT);
      pinMode(this->_pin6, OUTPUT);
      pinMode(this->_pin7, OUTPUT);
      pinMode(this->_pin8_dot, OUTPUT);
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
      digitalWrite(this->_pin1, HIGH);
      digitalWrite(this->_pin2, HIGH);
      digitalWrite(this->_pin3, HIGH);
      digitalWrite(this->_pin4, HIGH);
      digitalWrite(this->_pin5, HIGH);
      digitalWrite(this->_pin6, HIGH);
      digitalWrite(this->_pin7, HIGH);
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
        digitalWrite(this->_pin8_dot, LOW);
      } else {
        // Point off
        digitalWrite(this->_pin8_dot, HIGH);
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
          digitalWrite(this->_pin1, HIGH);
          digitalWrite(this->_pin2, LOW);
          digitalWrite(this->_pin3, LOW);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, LOW);
          digitalWrite(this->_pin6, LOW);
          digitalWrite(this->_pin7, LOW);
          break;
        case 1:
          digitalWrite(this->_pin1, HIGH);
          digitalWrite(this->_pin2, HIGH);
          digitalWrite(this->_pin3, HIGH);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, HIGH);
          digitalWrite(this->_pin6, HIGH);
          digitalWrite(this->_pin7, LOW);
          break;
        case 2:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, HIGH);
          digitalWrite(this->_pin3, LOW);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, LOW);
          digitalWrite(this->_pin6, LOW);
          digitalWrite(this->_pin7, HIGH);
          break;
        case 3:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, HIGH);
          digitalWrite(this->_pin3, LOW);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, HIGH);
          digitalWrite(this->_pin6, LOW);
          digitalWrite(this->_pin7, LOW);
          break;
        case 4:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, LOW);
          digitalWrite(this->_pin3, HIGH);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, HIGH);
          digitalWrite(this->_pin6, HIGH);
          digitalWrite(this->_pin7, LOW);
          break;
        case 5:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, LOW);
          digitalWrite(this->_pin3, LOW);
          digitalWrite(this->_pin4, HIGH);
          digitalWrite(this->_pin5, HIGH);
          digitalWrite(this->_pin6, LOW);
          digitalWrite(this->_pin7, LOW);
          break;
        case 6:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, HIGH);
          digitalWrite(this->_pin3, LOW);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, LOW);
          digitalWrite(this->_pin6, LOW);
          digitalWrite(this->_pin7, LOW);
          break;
        case 7:
          digitalWrite(this->_pin1, HIGH);
          digitalWrite(this->_pin2, HIGH);
          digitalWrite(this->_pin3, LOW);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, HIGH);
          digitalWrite(this->_pin6, HIGH);
          digitalWrite(this->_pin7, LOW);
          break;
        case 8:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, LOW);
          digitalWrite(this->_pin3, LOW);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, LOW);
          digitalWrite(this->_pin6, LOW);
          digitalWrite(this->_pin7, LOW);
          break;
        case 9:
          digitalWrite(this->_pin1, LOW);
          digitalWrite(this->_pin2, LOW);
          digitalWrite(this->_pin3, LOW);
          digitalWrite(this->_pin4, LOW);
          digitalWrite(this->_pin5, HIGH);
          digitalWrite(this->_pin6, HIGH);
          digitalWrite(this->_pin7, LOW);
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
