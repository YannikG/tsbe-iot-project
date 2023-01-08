#include <Arduino.h>

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
    byte pin;
    void init();
  public:
    TrackCurrent(byte pin);
    bool hasCurrent();
    void upCurrent();
    void downCurrent();
    void onLoop();
};