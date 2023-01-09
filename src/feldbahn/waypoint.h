#include <Arduino.h>
#include "Indicator.h"

#pragma once

class Waypoint
{
  private:
    Indicator *indicator;
  public:
    Waypoint(Indicator *indicator);
    void onLoop();
    bool isOccupied();
};