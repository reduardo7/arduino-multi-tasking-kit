#include "App_Runnable.h"

/**
   @see http://paulmurraycbr.github.io/ArduinoTheOOWay.html
*/

Runnable::Runnable() {
  nextRunnable = headRunnable;
  headRunnable = this;
}

static void Runnable::setupAll() {
  Serial.begin(9600);
  
  for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
    r->setup();
  }
}

static void Runnable::loopAll() {
  for (Runnable *r = headRunnable; r; r = r->nextRunnable) {
    r->loop();
  }
}

Runnable *Runnable::headRunnable = NULL;

/*
  # Code Example:

  void setup() {
    Runnable::setupAll();
  }

  void loop() {
    Runnable::loopAll();
  }
*/
