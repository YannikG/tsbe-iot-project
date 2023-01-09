#include <Arduino.h>

// set the debounce value for buttons.
#ifndef BUTTON_DEBOUNCE_DELAY
  #define BUTTON_DEBOUNCE_DELAY 400
#endif

#pragma once

class Button
{
  private:
    bool currentState;
    byte buttonToggledStateCounter = 0;
    bool lastReadingState;
    bool holdSateFlag;
    unsigned long lastDebounceTime = 0;
    byte pin;
    void init();
    void updateStateWithoutHoldingState(bool newState);
    void updateStateWithHoldingState(bool newState);
  public:
    Button(byte pin, bool holdStateFlag);
    bool getState();
    void onLoop();
};