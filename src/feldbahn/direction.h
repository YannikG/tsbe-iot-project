#ifndef DIRECTION_FORWARD
  #define DIRECTION_FORWARD 1
#endif
#ifndef DIRECTION_BACKWARD
  #define DIRECTION_BACKWARD 0
#endif

#ifndef DIRECTION_CHANGE_SAFE_DELAY
  #define DIRECTION_CHANGE_SAFE_DELAY 1000
#endif

#include <Arduino.h>
#include "trackcurrent.h"

#pragma once

class Direction
{
  private:
    bool currentDirectionSate;
    void init();
    byte pin;
    TrackCurrent *trackCurrent;
    void safeupdateDirection(bool newDirection);
  public:
    Direction(byte pin, TrackCurrent *trackCurrent);
    bool getDirectionState();
    void switchDirection();
    void goForward();
    void goBackwords();
    void onLoop();
};

