#include "App_Runnable.h"
#include "Component_Led.h"
#include "Component_ProximityCheck.h"
#include "Component_LedDisplay.h"
#include "Component_Button.h"

/* **************************************************************************** */

// LedDisplay disp(11, 10, 9, 8, 7, 6, 5, 4);
// Button btnAdd(2);
// Button btnMin(3);
// byte num = 0;

// void setup() {
//  Runnable::setupAll();
// }

// void loop() {
//  Runnable::loopAll();

//  if (btnAdd.isClicked()) {
//    num++;
//  }

//  if (btnMin.isClicked()) {
//    num--;
//  }

//  disp.set(num);
// }

/* **************************************************************************** */

// Led ledState(13);
// Led ledErr(12);
// ProximityCheck pc(2, A0);
// Button btn(3);

// void setup() {
//  Runnable::setupAll();
// }

// void loop() {
//  Runnable::loopAll();

//  if (btn.isClicked()) {
//    ledErr.off();
//    pc.calibrate();
//  } else {
//    switch (pc.getState()) {
//      case ProximityCheckState::PROXIMITY:
//        ledErr.off();
//        ledState.on();
//        break;
//      case ProximityCheckState::NO_PROXIMITY:
//        ledErr.off();
//        ledState.off();
//        break;
//      case ProximityCheckState::ERROR_FIRST_CHECK:
//        ledState.off();
//        ledErr.on();
//        break;
//    }
//  }
// }

/* **************************************************************************** */

// Led ledState(2);
// Led ledErr(3);
// Button btn(5);
// bool x = true;

// void setup() {
//   Runnable::setupAll();
//   ledErr.flash(500, 10);
//   ledState.flash(500, 0);
// }

// void loop() {
//   Runnable::loopAll();

//   if (ledState.isFlashing()) {
//     ledErr.on();
//   } else {
//     ledErr.off();
//   }
// }

/* **************************************************************************** */

// Led led(13);

// void setup() {
//   Runnable::setupAll();
//   led.flash(500, 5);
// }

// void loop() {
//   Runnable::loopAll();

//   if (!led.isFlashing()) {
//     led.off();
//   }
// }

/* **************************************************************************** */

Led l1(9);
Led l2(10);
Led l3(11);
Led l4(LED_BUILTIN);
Button btn(2);

void setup() {
  Runnable::setupAll();
  //pinMode(7, OUTPUT);
  //digitalWrite(7, HIGH);
  //pinMode(3, INPUT);
  // Serial.begin(9600);
}

void loop() {
  Runnable::loopAll();

  if (btn.isClicked()) {
    l1.invert();
  }

  if (btn.isLongClick()) {
    l2.invert();
  }

  if (btn.isShortClick()) {
    l3.invert();
  }

  if (btn.isDown()) {
    l4.on();
  } else {
    l4.off();
  }
}

/* **************************************************************************** */
