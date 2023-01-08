#include "HardwareSerial.h"
#include "trackcurrent.h"
#include <Arduino.h>
#include "led.h"

TrackCurrent::TrackCurrent(byte pin, LED *led)
{
  this->pin = pin;
  this->led = led;
  this->upAfterDelay = 0;
  this->lastDebounceTimeSet = false;
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
  Serial.println("track current now: OFF");
  this->onLoop();
}

void TrackCurrent::upCurrent()
{
  this->currentState = TRACK_CURRENT_ON;
  Serial.println("track current now: ON");
  this->onLoop();
}

void TrackCurrent::upCurrentAfterDelay(unsigned long delay)
{
  this->upAfterDelay = delay;
  this->upCurrent();
}

void TrackCurrent::onLoop()
{
  if (this->currentState == TRACK_CURRENT_OFF)
  {
    digitalWrite(this->pin, this->currentState);
    this->upAfterDelay = 0;
    this->led->off();
  }
  else if (this->currentState == TRACK_CURRENT_ON)
  {
    if (this->lastDebounceTimeSet == false)
    {
      this->lastDebounceTime = millis();
      this->lastDebounceTimeSet = true;
    }
    else if (this->lastDebounceTimeSet == true && millis() - this->lastDebounceTime > this->upAfterDelay)
    {
      this->lastDebounceTimeSet = false;
      digitalWrite(this->pin, this->currentState);
      this->led->on();
      this->upAfterDelay = 0;
    }   
  }

  this->led->onLoop();
}

bool TrackCurrent::hasCurrent() {
  return this->currentState;
}