#include "HardwareSerial.h"
#include "button.h"
#include <Arduino.h>

Button::Button(byte pin, bool holdStateFlag)
{
  this->pin = pin;
  this->holdSateFlag = holdStateFlag;
  this->init();
}
// init the pin and set some default values.
void Button::init()
{
  pinMode(this->pin, INPUT);
  this->currentState = false;
  this->buttonToggledStateCounter = 0;
}

// returns the current button state.
bool Button::getState()
{
  return this->currentState;
}

// update the state without holding the state. (press = 1, release = 0).
void Button::updateStateWithoutHoldingState(bool newState)
{
  this->currentState = newState;
}

// update the sate with holding the state. (1. press = 1, release = no change, 2. press = 0).
void Button::updateStateWithHoldingState(bool newState)
{
    // we keep track of how often we have pressed the button.
    if (newState == true && this->buttonToggledStateCounter < 2) 
    {
      this->buttonToggledStateCounter++;
    }
    // When the button currently is turned off and we press it, the button should be switched to on.
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

// should be called from inside the loop() function.
void Button::onLoop()
{
  // The circuit for our buttons return a HIGH as OFF and a LOW as ON.
  // this reduces the interfering of other electronics.
  bool newReadingState = !digitalRead(this->pin);

  // When the value is different, we set our debounce time.
  if (newReadingState != this->lastReadingState)
  {
    this->lastDebounceTime = millis();
  }

  // Start the logic when the debounce delay has elapsed and the last reading is not the same as the current reading.
  if (millis() - this->lastDebounceTime < BUTTON_DEBOUNCE_DELAY && newReadingState != this->lastReadingState)
  {
    // check how we should update our state.
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








