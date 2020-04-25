#ifndef LIB_COMPONENT_LED_DISPLAY8
#define LIB_COMPONENT_LED_DISPLAY8

#include <Arduino.h>
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
    const PinOutDigital _pin1;
    const PinOutDigital _pin2;
    const PinOutDigital _pin3;
    const PinOutDigital _pin4;
    const PinOutDigital _pin5;
    const PinOutDigital _pin6;
    const PinOutDigital _pin7;
    const PinOutDigital _pin8_dot;

  protected:
    void setup();
    void loop();

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
    );

    /**
     * Turn off all leds.
     *
     * @return This instance.
     */
    LedDisplay8* off();

    /**
     * Set point state.
     *
     * @param status Point status. True to turn it on, False to turn it off.
     * @return This instance.
     */
    LedDisplay8* setPoint(bool status);

    /**
     * Set display number.
     *
     * @param n Number to display.
     * @param point Point status. True to turn it on, False to turn it off.
     * @return This instance.
     */
    LedDisplay8* set(uint8_t n, bool point = false);
};

#endif
