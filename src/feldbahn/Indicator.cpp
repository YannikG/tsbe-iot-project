#include "HardwareSerial.h"
#include "Arduino.h"
#include "Indicator.h"

Indicator::Indicator(byte pin) {
  this->pin = pin;
  this->currentState = 0;

  this->init();
}

// init the pin.
void Indicator::init() {
  pinMode(this->pin, INPUT);
}

// check the state 
void Indicator::checkState() {
  
  // The circuit for indicators return a HIGH as OFF and a LOW as ON.
  // this reduces the interfering of other electronics.
  bool newReading = !digitalRead(this->pin);

  // When the value is different, we set our debounce time.
  if (newReading != this->lastReading)
  {
    this->lastDebounceTime = millis();
  }

  // Start the logic when the debounce delay has elapsed.
  if (millis() - this->lastDebounceTime > INDICATOR_DEBOUNCE_DELAY)
  {
    // reading an unoccupied state, we count up to avoid any false positives.
    if (newReading == false && this->currentState == true && this->zeroCounter < INDICATOR_0_COUNTER_THRESHOLD)
    {
      this->zeroCounter++;
    }
    // when we still receive a unoccupied and have reached our counter, we can assume there is currently no train near the indicator.
    else if (newReading == false && this->currentState == true && this->zeroCounter >= INDICATOR_0_COUNTER_THRESHOLD)
    {
      this->currentState = newReading;
      this->zeroCounter = 0;
    }
    // When the indicator is occupied we want to know it immediately.
    else if (newReading == true && this->currentState == false)
    {
      this->currentState = newReading;
    }
  }

  this->lastReading = newReading;
}

// returns the current state of the indicator.
bool Indicator::getState()
{
  return this->currentState;
}








