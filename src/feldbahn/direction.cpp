#include "HardwareSerial.h"
#include <Arduino.h>
#include "direction.h"
#include "trackcurrent.h"

Direction::Direction(byte pin, TrackCurrent *trackCurrent)
{
  this->pin = pin;
  this->trackCurrent = trackCurrent;
  this->init();
}

// init the pin.
void Direction::init()
{
  pinMode(this->pin, OUTPUT);
  // 0 is default independent of DIRECTION_FORWARD or DIRECTION_BACKWARD
  this->currentDirectionSate = 0;
}

// get the current direction state.
bool Direction::getDirectionState()
{
  return this->currentDirectionSate;
}

// switch the direction to forward
void Direction::goForward()
{
  this->safeUpdateDirection(DIRECTION_FORWARD);
  Serial.println("direction new: FORWARD");
  this->onLoop();
}

// switch the direction to backwards
void Direction::goBackwards()
{
  this->safeUpdateDirection(DIRECTION_BACKWARD);
  Serial.println("direction new: BACKWARDS");
  this->onLoop();
}

// switch the direction according to the current direction of travel.
void Direction::switchDirection()
{
  if (this->currentDirectionSate == DIRECTION_FORWARD)
  {
    this->goBackwards();
  }
  else if (this->currentDirectionSate == DIRECTION_BACKWARD)
  {
    this->goForward();
  }
}

// main logic.
void Direction::onLoop()
{
  digitalWrite(this->pin, this->currentDirectionSate);
}

// to avoid any issues with the motor of the locomotive, we apply some safety measurements to prevent any damages.
void Direction::safeUpdateDirection(bool newDirection)
{
  bool hasCurrentlyCurrentOnTrack = this->trackCurrent->hasCurrent();

  // before we switch the direction, we turn the track current down.
  this->trackCurrent->downCurrent();

  // change the direction.
  this->currentDirectionSate = newDirection;

  // only power the track again when it was already turned on before the direction change.
  if (hasCurrentlyCurrentOnTrack == true)
  {
    // turn the track current back on after a safe delay.
    this->trackCurrent->upCurrentAfterDelay(DIRECTION_CHANGE_SAFE_DELAY);
  }
}













