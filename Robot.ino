const int LS_PIN_IN = A0;
const int LS_PIN_OUT = 2;
const int LS_PIN_ERR = 12;
const int LS_SW_PIN = 3;
//const int SW_PIN = 3;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(LS_PIN_ERR, OUTPUT);
  ProximityCheckSetup(LS_SW_PIN, LS_PIN_IN, LS_PIN_OUT);
  
//  SwitchSetup(SW_PIN);
}

void loop() {
  digitalWrite(LS_PIN_ERR, LOW);
      
  switch (ProximityCheckLoop()) {
    case 0:
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    case 1:
      digitalWrite(LED_BUILTIN, LOW);
      break;
    case 2:
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(LS_PIN_ERR, HIGH);
      break;
    case 3:
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(LS_PIN_ERR, HIGH);
      delay(500);
      digitalWrite(LS_PIN_ERR, LOW);
      delay(100);
      digitalWrite(LS_PIN_ERR, HIGH);
      delay(500);
      break;
  }

//  if (SwitchLoop()) {
//    digitalWrite(LED_BUILTIN, HIGH);
//  } else {
//    digitalWrite(LED_BUILTIN, LOW);
//  }
}
