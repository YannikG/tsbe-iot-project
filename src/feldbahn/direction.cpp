#include <Arduino.h>
#include "direction.h"

Direction::Direction(byte pin)
{
  this->pin = pin;
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
  this->currentDirectionSate = DIRECTION_FORWARD;
}

void Direction::goBackwords()
{
  this->currentDirectionSate = DIRECTION_BACKWARD;
}

void Direction::onLoop()
{
  digitalWrite(this->pin, this->currentDirectionSate);
}





