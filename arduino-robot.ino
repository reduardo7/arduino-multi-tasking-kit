using namespace std;

/**
   @see http://paulmurraycbr.github.io/ArduinoTheOOWay.html
*/
class Runnable {
  private:
    static Runnable *headRunnable;
    Runnable *nextRunnable;

  public:
    Runnable() {
      nextRunnable = headRunnable;
      headRunnable = this;
    }

    virtual void setup() = 0;
    virtual void loop() = 0;

    static void setupAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
        r->setup();
      }
    }

    static void loopAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
        r->loop();
      }
    }
};
Runnable *Runnable::headRunnable = NULL;

template <typename T>
unsigned long arrayLen(T *x) {
  return sizeof(x) / sizeof(x[0]);
}

/**
   @connection
    {pin} <> [Led +]
    (-) <> [Led -]
*/
class Led: public Runnable {
  private:
    const byte _pin;
    unsigned int _flash_duration = -1;
    unsigned int _flash_times = -1;
    unsigned int _flash_index = -1;
    unsigned long _flash_time = 0;
    unsigned long _flash_last_time = 0;

  public:
    Led(byte pin):
      _pin(pin)
    {}

    void setup() {
      pinMode(_pin, OUTPUT);
      off();
    }

    void loop() {
      unsigned long m = millis();

      if (isFlashing() && (m - _flash_last_time) >= _flash_duration) {
        invert();
        _flash_last_time = m;

        if (_flash_times > 0) {
          _flash_index++;
        }
      }
    }

    bool isFlashing() {
      return (_flash_times <= 0 && _flash_duration > 0) || (_flash_index >= 0 && _flash_index < _flash_times);
    }

    void on() {
      digitalWrite(_pin, HIGH);
    }

    void off() {
      digitalWrite(_pin, LOW);
    }

    void invert() {
      set(!getState());
    }

    void set(bool state) {
      if (state) {
        on();
      } else {
        off();
      }
    }

    bool getState() {
      return digitalRead(_pin) == HIGH;
    }

    void flash(unsigned int duration, unsigned int times) {
      _flash_duration = duration;
      _flash_times = times * 2; // One time on, one time off | times <= 0 : forever
      _flash_index = 0;
      _flash_last_time = millis();
    }

    void flashStop() {
      _flash_duration = 0;
    }
};

/**
   Button State
   @see Button
*/
enum ButtonState {
  NO = 0,
  SHORT = 1,
  LONG = 2
};

/**
   @see ButtonState
   @connection
    {pin} <> [Switch] <> (-)
*/
class Button: public Runnable {
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

    bool isShortClick() {
      return _result == ButtonState::SHORT;
    }

    bool isLongClick() {
      return _result == ButtonState::LONG;
    }
};

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
    const Led _led;
    const byte _apin_in;

    // First should be LOW, to check external light
    const bool _STEPS[4] = {
      false, true, false, true
    };
    int _STEPS_LEN;

    byte _result = ProximityCheckState::NO_PROXIMITY;
    int _prox = 800;

    byte _checkInputState(bool state) {
      _led.set(state);
      delay(50);
      return analogRead(_apin_in);
    }

    int _calibrateMin() {
      int r = 1000;

      for (int i = 0; i < 3; i++) {
        int x = _checkInputState(false);
        if (x < r) r = x;
        delay(1000);
      }

      return r;
    }

    int _calibrateMax() {
      int r = 0;

      for (int i = 0; i < 3; i++) {
        int x = _checkInputState(true);
        if (x > r) r = x;
        delay(1000);
      }

      return r;
    }

  public:
    ProximityCheck(byte led_pin, byte apin_in) :
      _led(led_pin),
      _apin_in(apin_in)
    {
      _STEPS_LEN = arrayLen(_STEPS);
    }

    void setup() {}

    void loop() {
      int i = 0;
      bool result = true;

      while (result && i < _STEPS_LEN) {
        bool state = _STEPS[i];
        byte x = _checkInputState(state);

        if (state) {
          result = x > _prox;
        } else {
          result = x < _prox;
        }

        if (!result && i == 0) {
          _result = ProximityCheckState::ERROR_FIRST_CHECK; // Error: First check is ON
        }

        i++;
      }

      if (result) {
        _result = ProximityCheckState::NO_PROXIMITY; // No proximity
      } else {
        _result = ProximityCheckState::PROXIMITY; // Proximity
      }
    }

    byte getState() {
      return _result;
    }

    void calibrate() {
      int b = _calibrateMax();
      int a = _calibrateMin();
      _prox = a + (b - a) / 2;
    }
};

/* **************************************************************************** */

Led ledState(13);
Led ledErr(12);
ProximityCheck pc(2, A0);
Button btn(3);

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

  if (btn.isClicked()) {
    ledErr.off();
    pc.calibrate();
  } else {
    switch (pc.getState()) {
      case ProximityCheckState::PROXIMITY:
        ledErr.off();
        ledState.on();
        break;
      case ProximityCheckState::NO_PROXIMITY:
        ledErr.off();
        ledState.off();
        break;
      case ProximityCheckState::ERROR_FIRST_CHECK:
        ledState.off();
        ledErr.on();
        break;
    }
  }

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
