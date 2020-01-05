/**
 * Connection:
 *  {pin} <> [Led -]
 *  (-) <> [Led +]
 */
class Led {
  private:
    const byte _pin;
    bool _state = false;
    
  public:
    Led(byte pin):
      _pin(pin)
      {}
    
    void setup() {
      pinMode(_pin, OUTPUT);
      off();
    }
    
    void on() {
      _state = true;
      digitalWrite(_pin, HIGH);
    }
    
    void off() {
      _state = false;
      digitalWrite(_pin, LOW);
    }

    void invert() {
      set(!_state);
    }
    
    void set(bool state) {
      if (state) {
        on();
      } else {
        off();
      }
    }
    
    bool getState() {
      return _state;
    }

    void flash(int durations[]) {
      for (int i = 0; i < sizeof(durations) / sizeof(durations[0]); i++) {
        invert();
        delay(durations[i]);
      }
    }
};

enum ButtonState {
  NO = 0,
  SHORT = 1,
  LONG = 2
};

/**
 * Connection:
 *  {pin} <> [Switch] <> (-)
 */
class Button {
  private:
    const byte _pin;
    int _state;
    unsigned long _buttonDownMs;
    ButtonState _result;
    
  public:
    Button(byte pin) :
      _pin(pin)
      { }
    
    void setup() {
      pinMode(_pin, INPUT_PULLUP);
      _state = HIGH;
      _result = ButtonState::NO;
    }

    void loop() {
      _result = ButtonState::NO;
      int prevState = _state;
      _state = digitalRead(_pin);
      
      if (prevState == HIGH && _state == LOW) {
        _buttonDownMs = millis();
      } else if (prevState == LOW && _state == HIGH) {
        if (millis() - _buttonDownMs < 50) {
          // ignore this for debounce
        } else if (millis() - _buttonDownMs < 500) {
          // short click
          _result = ButtonState::SHORT;
        } else {
          // long click
          _result = ButtonState::LONG;
        }
      }
    }

    ButtonState getState() {
      return _result;
    }

    bool isClicked() {
      return _result != ButtonState::NO;
    }
};

// https://pimylifeup.com/arduino-light-sensor/
//class ProximityCheck {
//  private:
//    Switch sw;
//    Led led;
//    byte apin_in;
//    int STEPS_LEN;
//    
//    const int prox = 800;
//    
//    // First should be LOW, to check external light
//    const int STEPS[4] = {
//      false, true, false, true
//    };
//    
//    byte _check(bool state) {
//      this->led->set(state);
//      delay(50);
//      return analogRead(this->apin_in);
//    }
//    
//    int _calibrateMin() {
//      int r = 1000;
//    
//      for (int i = 0; i < 3; i++) {
//        int x = this->_check(false);
//        if (x < r) {
//          r = x;
//        }
//        delay(1000);
//      }
//      
//      return r;
//    }
//    
//    int _calibrateMax() {
//      int r = 0;
//    
//      for (int i = 0; i < 3; i++) {
//        int x = this->_check(true);
//        if (x > r) {
//          r = x;
//        }
//        delay(1000);
//      }
//      
//      return r;
//    }
//
//  public:
//    ProximityCheck(byte sw_pin, byte led_pin, byte apin_in) {
//      this->sw(sw_pin);
//      this->led(led_pin);
//      this->apin_in = apin_in;
//
//      this->STEPS_LEN = sizeof(this->STEPS) / sizeof(this->STEPS[0]);
//    }
//    
//    byte doLoop() {
//      bool calibrate = this->sw->getState();
//    
//      if (calibrate) {
//        this->calibrate();
//        return 3; // Calibration completed
//      } else {
//        return this->getState();
//      }
//    }
//    
//    byte getState() {
//      int i = 0;
//      bool result = true;
//      
//      while (result && i < this->STEPS_LEN) {
//        bool state = this->STEPS[i];
//        bool x = this->_check(state);
//        
//        if (state) {
//          result = x > this->prox;
//        } else {
//          result = x < this->prox;
//        }
//    
//        if (!result && i == 0) {
//          return 2; // Error: First check is ON
//        }
//        
//        i++;
//      }
//      
//      if (result) {
//        return 0; // No proximity
//      } else {
//        return 1; // Proximity
//      }
//    }
//    
//    void calibrate() {
//      int a = this->_calibrateMin();
//      int b = this->_calibrateMax();
//      this->prox = a + (b - a) / 2;
//    }
//};

Led ledState(LED_BUILTIN);
Led ledErr(12);
//ProximityCheck pc(3, 2, A0);
Button btn(3);

int fs[] = {100, 100, 100, 100, 100, 100, 100};
int fl[] = {500, 100, 500, 100, 500, 100, 500};

void setup() {
  ledState.setup();
  ledErr.setup();
  btn.setup();
}

void loop() {
  btn.loop();
//  ledErr.off();
//      
//  switch (pc.doLoop()) {
//    case 0:
//      ledState.on();
//      break;
//    case 1:
//      ledState.off();
//      break;
//    case 2:
//      ledState.off();
//      ledErr.on();
//      break;
//    case 3:
//      ledState.off();
//      ledErr.on();
//      delay(500);
//      ledErr.off();
//      delay(100);
//      ledErr.on();
//      delay(500);
//      break;
//  }

  switch (btn.getState()) {
    case ButtonState::NO:
      break;
    case ButtonState::SHORT:
      ledState.invert();
      break;
    case ButtonState::LONG:
      ledErr.invert();
      break;
  }

//  if (btn.isClicked()) {
//    ledState.invert();
//  }
}
