// https://pimylifeup.com/arduino-light-sensor/

int _pc_sw_pin = -1;
int _pc_apin_in = -1;
int _pc_pin_out = -1;

int _pc_prox = 800;

// First should be LOW, to check external light
const int _PC_STEPS[] = {
  LOW, HIGH, LOW, HIGH
};

void ProximityCheckSetup(int sw_pin, int apin_in, int pin_out) {
  _pc_sw_pin = sw_pin;
  _pc_apin_in = apin_in;
  _pc_pin_out = pin_out;
  
  pinMode(sw_pin, INPUT);
  pinMode(pin_out, OUTPUT);
}

int ProximityCheckLoop() {
  int sw_state = digitalRead(_pc_sw_pin);

  if (sw_state == HIGH) {
    _pc_calibrate();
    delay(300);
    return 3;
  } else {
    return _pc_calc();
  }
}

int _pc_check(int state) {
  digitalWrite(_pc_pin_out, state);
  delay(50);
  return analogRead(_pc_apin_in);
}

void _pc_calibrate() {
  int a = _pc_calibrateMin();
  int b = _pc_calibrateMax();
  _pc_prox = a + (b - a) / 2;
}

int _pc_calibrateMin() {
  int r = 1000;
  int x;

  for (int i = 0; i < 3; i++) {
    x = _pc_check(LOW);
    if (x < r) {
      r = x;
    }
    delay(1000);
  }
  
  return r;
}

int _pc_calibrateMax() {
  int r = 0;
  int x;

  for (int i = 0; i < 3; i++) {
    x = _pc_check(HIGH);
    if (x > r) {
      r = x;
    }
    delay(1000);
  }
  
  return r;
}

int _pc_calc() {
  int state;
  int x;
  int i = 0;
  bool result = true;
  
  while (result && i < (sizeof(_PC_STEPS) / sizeof(_PC_STEPS[0]))) {
    state = _PC_STEPS[i];
    x = _pc_check(state);
    
    if (state == HIGH) {
      result = x > _pc_prox;
    } else {
      result = x < _pc_prox;
    }

    if (!result && i == 0) {
      return 2;
    }
    
    i++;
  }
  
  if (result) {
    return 0;
  } else {
    return 1;
  }
}
