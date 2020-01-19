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

    static void setupAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
        r->setup();
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

  public:
    Led(byte pin):
      _pin(pin)
    {}

    void setup() {
      pinMode(_pin, OUTPUT);
      off();
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
};

/**
   @see ButtonState
   @connection
    {pin} <> [Switch] <> (-)
*/
class Button: public Runnable {
  private:
    const byte _pin;

  public:
    Button(byte pin) :
      _pin(pin)
    { }

    void setup() {
      pinMode(_pin, INPUT);
    }

    bool isClicked() {
      bool r = digitalRead(_pin) == HIGH;
      delay(200);
      return r;
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

    ProximityCheckState getState() {
      int i = 0;
      bool result = true;
      ProximityCheckState _result;

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

//    if (btn.isClicked()) {
//      ledState.invert();
//    }
}
