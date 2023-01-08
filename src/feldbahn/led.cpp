#include "led.h"
#include <Arduino.h>

LED::LED(byte pin)
{
  this->pin = pin;
  this->currentState = false;
  this->init();
}

void LED::init()
{
  pinMode(this->pin, OUTPUT);
}

void LED::off()
{
  this->currentState = false;
}

void LED::on()
{
  this->currentState = true;
}

bool LED::getState() 
{
  return this->currentState;
}

void LED::onLoop()
{
  digitalWrite(this->pin, this->currentState);
}












