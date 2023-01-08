#include "HardwareSerial.h"
#include "button.h"
#include <Arduino.h>

Button::Button(byte pin, bool holdStateFlag)
{
  this->pin = pin;
  this->holdSateFlag = holdStateFlag;
  this->init();
}

void Button::init()
{
  pinMode(this->pin, INPUT);
  this->currentState = false;
  this->buttonToggledStateCounter = 0;
}

bool Button::getState()
{
  return this->currentState;
}

void Button::updateStateWithoutHoldingState(bool newState)
{
  this->currentState = newState;
}

void Button::updateStateWithHoldingState(bool newState)
{
    // we keep track of how often we have pressed the button.
    if (newState == true && this->buttonToggledStateCounter < 2) 
    {
      this->buttonToggledStateCounter++;
    }
    // When button currently is turend off and we press it, the button should be switched to on.
    if (this->currentState == false && newState == true) {
      this->currentState = true;
    }
    // When the button has currently is turned on and we now press it again, we switch the state back to uff
    else if (this->currentState == true && newState == true && this->buttonToggledStateCounter == 2)
    {
      this->currentState = false;
      this->buttonToggledStateCounter = 0;
    }
}

void Button::onLoop()
{
  bool newReadingState = !digitalRead(this->pin);

  if (newReadingState != this->lastReadingState)
  {
    this->lastDebounceTime = millis();
  }

  if (millis() - this->lastDebounceTime < BUTTON_DEBOUNCE_DELAY && newReadingState != this->lastReadingState)
  {
    if (this->holdSateFlag == true)
    {
      this->updateStateWithHoldingState(newReadingState);
    }
    else
    {
      this->updateStateWithoutHoldingState(newReadingState);
    }
  }

  this->lastReadingState = newReadingState;
}








