#include "feldbahn.h"
#include "waypoint.h"
#include "trackcurrent.h"
#include "direction.h"
#include "button.h"
#include "led.h"
#include "state.h"

// objects
Waypoint stationA (new Indicator(IN_REED_STATION_A));
Waypoint curveWaypoint (new Indicator(IN_REED_CURVE));
Waypoint stationB (new Indicator(IN_REED_STATION_B));

TrackCurrent trackCurrent (OUT_TRACK_CURRENT, new LED(LED_BUILTIN));
Direction direction (OUT_DIRECTION_SWITCH, &trackCurrent);

Button layoutToggleButton (IN_BUTTON_START, true);
Button directionToggleButton (IN_BUTTON_DIRECTION, false);

// states
bool stationALastState = false;
bool stationBLastState = false;
bool curveWaypointLastState = false;

bool layoutToggleButtonLastState = false;
bool directionToggleButtonLastState = false;


void setup() {
  Serial.begin(9600);
  Serial.println(F("done setup!"));
}

void loop() {
  // call onLoop();
  layoutToggleButton.onLoop();
  directionToggleButton.onLoop();
  trackCurrent.onLoop();
  stationA.onLoop();
  stationB.onLoop();
  curveWaypoint.onLoop();
  direction.onLoop();

  // updates on Button clicks.
  updateCurrentOnButtonClick();
  updateDirectionOnButtonClick();

  updateOnWaypointReached(&stationA, &stationALastState, DIRECTION_FORWARD, "Station A");
  updateOnWaypointReached(&stationB, &stationBLastState, DIRECTION_BACKWARD, "Station B");
  nodifyWaypointPassed(&curveWaypoint, &curveWaypointLastState, "Curve Waypoint");
}

void updateCurrentOnButtonClick()
{
  bool newButtonState = layoutToggleButton.getState();

  if (hasStateChanged(newButtonState, layoutToggleButtonLastState))
  {
    if (newButtonState == true && trackCurrent.hasCurrent() == false) 
    {
      trackCurrent.upCurrent();
    }
    else
    {
      trackCurrent.downCurrent();
    }

    layoutToggleButtonLastState = newButtonState;
  }
}

void updateDirectionOnButtonClick()
{
  bool newButtonState = directionToggleButton.getState();

  if (hasStateChanged(newButtonState, directionToggleButtonLastState))
  {
    if (newButtonState == true)
    {
      direction.switchDirection();
    }
    directionToggleButtonLastState = newButtonState;
  }
}

void updateOnWaypointReached(Waypoint *waypoint, bool *waypointState, bool nextDirection, String stationName)
{
  bool newWaypointState = waypoint->isOccupied();
  bool &currentWaypointState = *waypointState;
  if (hasStateChanged(newWaypointState, currentWaypointState))
  {
    Serial.print(stationName);
    Serial.print(':');
    if (newWaypointState == true)
    {
      Serial.println(" occupied");

      bool wasTrackCurrentOnBeforeSwitch = trackCurrent.hasCurrent();
      trackCurrent.downCurrent();
      if (nextDirection == DIRECTION_FORWARD)
      {
        direction.goForward();
      }
      else
      {
        direction.goBackwords();
      }

      if (wasTrackCurrentOnBeforeSwitch) 
      {
        trackCurrent.upCurrentAfterDelay(STATION_WAIT_TIME);
      }
    }
    else
    {
      Serial.println(" unoccupied");
    }

    *waypointState = newWaypointState;
  }
}

void nodifyWaypointPassed(Waypoint *waypoint, bool *waypointState, String stationName)
{
  bool newWaypointState = waypoint->isOccupied();
  if (hasStateChanged(newWaypointState, *waypointState))
  {
    Serial.print(stationName);
    Serial.print(':');
    if (newWaypointState == true)
    {
      Serial.println(" occupied");
    }
    else
    {
      Serial.println(" unoccupied");
    }

    waypointState = &newWaypointState;
  }
}









