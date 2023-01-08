#include "HardwareSerial.h"
#include <Arduino.h>
#include "direction.h"
#include "trackcurrent.h"

Direction::Direction(byte pin, TrackCurrent *trackCurrent)
{
  this->pin = pin;
  this->trackCurrent = trackCurrent;
}

void Direction::init()
{
  pinMode(this->pin, OUTPUT);
  // 0 is default independent of DIRECTION_FORWARD or DIRECTION_BACKWARD
  this->currentDirectionSate = 0;
}

bool Direction::getDirectionState()
{
  return this->currentDirectionSate;
}

void Direction::goForward()
{
  this->safeupdateDirection(DIRECTION_FORWARD);
  Serial.println("direction new: FORWARD");
  this->onLoop();
}

void Direction::goBackwords()
{
  this->safeupdateDirection(DIRECTION_BACKWARD);
  Serial.println("direction new: BACKWARDS");
  this->onLoop();
}

void Direction::switchDirection()
{
  if (this->currentDirectionSate == DIRECTION_FORWARD)
  {
    this->goBackwords();
  }
  else if (this->currentDirectionSate == DIRECTION_BACKWARD)
  {
    this->goForward();
  }
}

void Direction::onLoop()
{
  digitalWrite(this->pin, this->currentDirectionSate);
}

void Direction::safeupdateDirection(bool newDirection)
{
  bool hasCurrentlyCurrentOnTrack = this->trackCurrent->hasCurrent();

  this->trackCurrent->downCurrent();

  this->currentDirectionSate = newDirection;

  // only power the track again when it was already turned on before the direction change.
  if (hasCurrentlyCurrentOnTrack == true)
  {
      this->trackCurrent->upCurrentAfterDelay(DIRECTION_CHANGE_SAFE_DELAY);
  }
}













