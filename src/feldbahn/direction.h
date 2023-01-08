#ifndef DIRECTION_FORWARD
  #define DIRECTION_FORWARD 1
#endif
#ifndef DIRECTION_BACKWARD
  #define DIRECTION_BACKWARD 0
#endif

#pragma once

class Direction
{
  private:
    bool currentDirectionSate;
    void init();
    byte pin;
  public:
    Direction(byte pin);
    bool getDirectionState();
    void goForward();
    void goBackwords();
    void onLoop();
};