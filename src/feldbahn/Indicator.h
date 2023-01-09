#include <Arduino.h>

// indicates how often a unoccupied must be ret before an indicator switches its state to unoccupied.
#ifndef INDICATOR_0_COUNTER_THRESHOLD
  #define INDICATOR_0_COUNTER_THRESHOLD 5
#endif

// debounce in ms.
#ifndef INDICATOR_DEBOUNCE_DELAY
  #define INDICATOR_DEBOUNCE_DELAY 200
#endif

#pragma once

class Indicator
{
  private:
    byte pin;
    bool currentState;
    bool lastReading;
    unsigned long lastDebounceTime = 0;
    short zeroCounter;
    void init();
  public:
    Indicator(byte pin);
    void checkState();
    bool getState();
};