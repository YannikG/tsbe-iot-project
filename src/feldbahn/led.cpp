#include "led.h"
#include <Arduino.h>

LED::LED(byte pin)
{
  this->pin = pin;
  this->currentState = false;
  this->init();
}

// init the pin.
void LED::init()
{
  pinMode(this->pin, OUTPUT);
}

// turn the LED off.
void LED::off()
{
  this->currentState = false;
}

// turn the LED on.
void LED::on()
{
  this->currentState = true;
}

// return the current LED state.
bool LED::getState() 
{
  return this->currentState;
}

// should be called inside the loop() function.
void LED::onLoop()
{
  // Write the current sate to the LED.
  digitalWrite(this->pin, this->currentState);
}












