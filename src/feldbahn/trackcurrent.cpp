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

// init the pin.
void TrackCurrent::init() 
{
  pinMode(this->pin, OUTPUT);
  this->downCurrent();
}

// changes the state of the track current to DOWN.
void TrackCurrent::downCurrent()
{
  this->currentState = TRACK_CURRENT_OFF;
  Serial.println("track current now: OFF");
  this->onLoop();
}

// changes the state of the track current to UP.
void TrackCurrent::upCurrent()
{
  this->currentState = TRACK_CURRENT_ON;
  Serial.println("track current now: ON");
  this->onLoop();
}

// changes the state of the track current to UP after a specified delay in ms.
void TrackCurrent::upCurrentAfterDelay(unsigned long delay)
{
  this->upAfterDelay = delay;
  Serial.print("track current will be in ");
  Serial.print(delay / 1000);
  Serial.println("s: ON");
  this->currentState = TRACK_CURRENT_ON;
  this->onLoop();
}

// main logic of the track current. must be called in the loop() function.
// gets also called after a state update has occurred.
void TrackCurrent::onLoop()
{
  // When the current should be shut down, we don't wait and turn it off immediately.
  if (this->currentState == TRACK_CURRENT_OFF)
  {
    digitalWrite(this->pin, this->currentState);

    // reduce the potential of bugs...
    this->upAfterDelay = 0;
    this->led->off();
  }
  // When the current should be up, we apply our logic.
  else if (this->currentState == TRACK_CURRENT_ON)
  {
    // When no debounce time was set, we set a debounce time.
    if (this->lastDebounceTimeSet == false)
    {
      this->lastDebounceTime = millis();
      this->lastDebounceTimeSet = true;
    }
    // When enough time has elapsed, we turn the current back on.
    else if (this->lastDebounceTimeSet == true && millis() - this->lastDebounceTime > this->upAfterDelay)
    {
      this->lastDebounceTimeSet = false;
      digitalWrite(this->pin, this->currentState);
      this->led->on();

      // don't forget to change the value back to 0!
      this->upAfterDelay = 0;
    }   
  }

  this->led->onLoop();
}

// returns the current state of the track current.
// this value is not accurate and is fully calculated. When the power supply for the track is not plugged in. This method ignore this fact!
bool TrackCurrent::hasCurrent() {
  return this->currentState;
}