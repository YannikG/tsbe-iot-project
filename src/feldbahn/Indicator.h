#include <Arduino.h>

#ifndef INDICATOR_0_COUNTER_THRESHOLD
  #define INDICATOR_0_COUNTER_THRESHOLD 5
#endif

#ifndef INDICATOR_DEBOUNCE_DELAY
  #define INDICATOR_DEBOUNCE_DELAY 50
#endif

#pragma once

#ifndef Indicator
  class Indicator
  {
    private:
      byte pin;
      bool currentState;
      bool lastReading;
      unsigned long lastDebounceTime = 0;
      short zeroCounter;
      // init the current indicator. this method must be called in the constructor!
      void init();
    public:
      Indicator(byte pin);
      // checks the pyhiscal state of the reed contact.
      void checkState();
      // returns the current state.
      bool getState();
  };
#endif