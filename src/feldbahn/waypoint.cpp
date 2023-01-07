#include "waypoint.h"
#include "Indicator.h"

Waypoint::Waypoint(Indicator *indicator)
{
  this->indicator = indicator;
}

bool Waypoint::isOccupied()
{
  return this->indicator->getState();
}

void Waypoint::onLoop()
{
  this->indicator->checkState();
}

Waypoint::~Waypoint()
{
  delete this->indicator;
  this->indicator = nullptr;
}