// describe what signal should be sent when the direction of travel is FORWARD.
#ifndef DIRECTION_FORWARD
  #define DIRECTION_FORWARD 0
#endif

// describe what signal should be sent when the direction of travel is BACKWARDS.
#ifndef DIRECTION_BACKWARD
  #define DIRECTION_BACKWARD 1
#endif

// set a safe delay to turn the track current back on after a direction change.
// DO NOT change to 0. Stay above 1000ms.
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
    void safeUpdateDirection(bool newDirection);
  public:
    Direction(byte pin, TrackCurrent *trackCurrent);
    bool getDirectionState();
    void switchDirection();
    void goForward();
    void goBackwards();
    void onLoop();
};

