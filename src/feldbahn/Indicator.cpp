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
  bool newState = !digitalRead(this->pin);

  // if (this->currentState != newState)
  // {
  //   this->currentState = newState;
  // }

  if (newState == false && this->currentState == true && this->zeroCounter < INDICATOR_0_COUNTER_THRESHOLD)
  {
    this->zeroCounter++;
  }
  else if (newState == false && this->currentState == true && this->zeroCounter >= INDICATOR_0_COUNTER_THRESHOLD)
  {
    this->currentState = newState;
    this->zeroCounter = 0;
  }
  else if (newState == true && this->currentState == false)
  {
    this->currentState = newState;
  }
}

bool Indicator::getState()
{
  return this->currentState;
}