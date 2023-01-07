#include <Arduino.h>
#include "Indicator.h"

#pragma once

class Waypoint
{
  private:
    Indicator *indicator;
  public:
    Waypoint(Indicator *indicator);
    // this method must be called in loop().
    void onLoop();
    // returns of a train has occupied the station.
    bool isOccupied();
    ~Waypoint();
};