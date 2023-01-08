#include <Arduino.h>
#include "led.h"

#ifndef TRACK_CURRENT_ON
  #define TRACK_CURRENT_ON 1
#endif
#ifndef TRACK_CURRENT_OFF
  #define TRACK_CURRENT_OFF 0
#endif

#pragma once

class TrackCurrent
{
  private:
    bool currentState;
    bool lastDebounceTimeSet;
    unsigned long upAfterDelay = 0;
    unsigned long lastDebounceTime = 0;
    byte pin;
    LED *led;
    void init();
  public:
    TrackCurrent(byte pin, LED *led);
    bool hasCurrent();
    void upCurrent();
    void upCurrentAfterDelay(unsigned long delay);
    void downCurrent();
    void onLoop();
};