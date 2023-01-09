#include "waypoint.h"
#include "Indicator.h"

// a Waypoint is currently a simple wrapper of an indicator but can be used in the future to call other functionalities like LED or Sounds...

Waypoint::Waypoint(Indicator *indicator)
{
  this->indicator = indicator;
}

// returns if a waypoint is occupied or not.
bool Waypoint::isOccupied()
{
  return this->indicator->getState();
}

// must be called in the main loop function.
void Waypoint::onLoop()
{
  this->indicator->checkState();
}