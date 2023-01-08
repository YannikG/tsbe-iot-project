#include <Arduino.h>
#pragma once

class LED
{
  private:
    bool currentState;
    byte pin;
    void init();
  public:
    LED(byte pin);
    void onLoop();
    void off();
    void on();
    bool getState();
};