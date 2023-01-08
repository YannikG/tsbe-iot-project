#include "trackcurrent.h"
#include <Arduino.h>

TrackCurrent::TrackCurrent(byte pin)
{
  this->pin = pin;
  this->init();
}

void TrackCurrent::init() 
{
  pinMode(this->pin, OUTPUT);
  this->downCurrent();
}

void TrackCurrent::downCurrent()
{
  this->currentState = TRACK_CURRENT_OFF;
}

void TrackCurrent::upCurrent()
{
  this->currentState = TRACK_CURRENT_ON;
}

void TrackCurrent::onLoop()
{
  digitalWrite(this->pin, this->currentState);
}

bool TrackCurrent::hasCurrent() {
  return this->currentState;
}