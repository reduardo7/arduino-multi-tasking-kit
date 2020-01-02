// https://www.arduino.cc/en/Tutorial/Button

int _pin_btn = -1;

int _sw_state = 0;
bool _sw_on = false;

void SwitchSetup(int pin_btn) {
  _pin_btn = pin_btn;
  pinMode(pin_btn, INPUT);
}

bool SwitchLoop() {
  _sw_state = digitalRead(_pin_btn);

  if (_sw_state == HIGH) {
    _sw_on = !_sw_on;
    delay(300);
  }

  return _sw_on;
}
