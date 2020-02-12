#include "App_Runnable.h"
#include "Component_Led.h"
#include "Component_ProximityCheck.h"
#include "Component_LedDisplay.h"
#include "Component_Button.h"

/* **************************************************************************** */

//Led ledState(13);
//Led ledErr(12);
//ProximityCheck pc(2, A0);
//Button btn(3);

LedDisplay disp(11, 10, 9, 8, 7, 6, 5, 4);
Button btnAdd(2);
Button btnMin(3);
byte num = 0;

void setup() {
  Runnable::setupAll();
  //  ledErr.flash(500, 10);
}

void loop() {
  Runnable::loopAll();

  //  if (x) {
  //    ledState.flash(500, 0);
  //    x = false;
  //  }
  //
  //  if (ledState.isFlashing()) {
  //    ledErr.on();
  //  } else {
  //    ledErr.off();
  //  }

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

  if (btnAdd.isClicked()) {
    num++;
  }
  if (btnMin.isClicked()) {
    num--;
  }

  disp.set(num);

  //  switch (btn.getState()) {
  //    case ButtonState::NO:
  //      break;
  //    case ButtonState::SHORT:
  //      ledState.invert();
  //      break;
  //    case ButtonState::LONG:
  //      ledErr.invert();
  //      break;
  //  }

  //  if (btn.isClicked()) {
  //    ledState.invert();
  //  }
}
