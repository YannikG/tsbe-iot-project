#include "HardwareSerial.h"
#include "Arduino.h"
#include "Indicator.h"

Indicator::Indicator(byte pin) {
  this->pin = pin;
  this->currentState = 0;

  this->init();
}

void Indicator::init() {
  pinMode(this->pin, INPUT);
}

void Indicator::checkState() {
  bool newReading = !digitalRead(this->pin);

  if (newReading != this->lastReading)
  {
    this->lastDebounceTime = millis();
  }

  if (millis() - this->lastDebounceTime > INDICATOR_DEBOUNCE_DELAY)
  {
    if (newReading == false && this->currentState == true && this->zeroCounter < INDICATOR_0_COUNTER_THRESHOLD)
    {
      this->zeroCounter++;
    }
    else if (newReading == false && this->currentState == true && this->zeroCounter >= INDICATOR_0_COUNTER_THRESHOLD)
    {
      this->currentState = newReading;
      this->zeroCounter = 0;
    }
    else if (newReading == true && this->currentState == false)
    {
      this->currentState = newReading;
    }
  }

  this->lastReading = newReading;
}

bool Indicator::getState()
{
  return this->currentState;
}








