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

// waypoint states.
bool stationALastState = false;
bool stationBLastState = false;
bool curveWaypointLastState = false;

// button states.
bool layoutToggleButtonLastState = false;
bool directionToggleButtonLastState = false;

// simple setup. Pin configuration happens in the individual classes (LED, TrackCurrent, Button, Indicator, etc).
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

  // actual logic.
  updateOnWaypointReached(&stationA, &stationALastState, DIRECTION_FORWARD, "Station A");
  updateOnWaypointReached(&stationB, &stationBLastState, DIRECTION_BACKWARD, "Station B");
  notifyWaypointPassed(&curveWaypoint, &curveWaypointLastState, "Curve Waypoint");
}

// update the track current based on user input.
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

// update the direction on button click.
void updateDirectionOnButtonClick()
{
  bool newButtonState = directionToggleButton.getState();

  if (hasStateChanged(newButtonState, directionToggleButtonLastState))
  {
    if (newButtonState == true)
    {
      // we don't care in what direction the train is currently moving. We want to update it to the other direction.
      direction.switchDirection();
    }
    directionToggleButtonLastState = newButtonState;
  }
}

// We want to execute some logic when a Waypoint was reached by the train (main logic of the operation ;) ).
void updateOnWaypointReached(Waypoint *waypoint, bool *waypointState, bool nextDirection, String stationName)
{
  bool newWaypointState = waypoint->isOccupied();

  // "hack" to get the actual value of the waypointState. passing &waypointState to hasStateChanged() always results in a true even when the state hasn't changed WHY?
  bool &currentWaypointState = *waypointState;

  if (hasStateChanged(newWaypointState, currentWaypointState))
  {
    Serial.print(stationName);
    Serial.print(':');
    if (newWaypointState == true)
    {
      Serial.println(" occupied");

      // We want to know if the tracks currently has a current. Because when it's down, maybe for a good reason...
      bool wasTrackCurrentOnBeforeSwitch = trackCurrent.hasCurrent();

      // Even though direction.go<<DIR>>() shuts down the current, we turn it off before switching the direction.
      trackCurrent.downCurrent();
      
      // nextDirection is set in the loop() function. Every station has its own preferred direction of travel.
      // with this behaviour we avoid a wrong direction switch when a Station is occupied multiple times by accident.
      if (nextDirection == DIRECTION_FORWARD)
      {
        direction.goForward();
      }
      else
      {
        direction.goBackwards();
      }

      // When we had current a few moments ago we want to switch it on again...
      if (wasTrackCurrentOnBeforeSwitch) 
      {
        // ... but a bit delayed.
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

// Sometimes we just want to get nodified when the train passes by a waypoint.
void notifyWaypointPassed(Waypoint *waypoint, bool *waypointState, String stationName)
{
  bool newWaypointState = waypoint->isOccupied();

  // "hack" to get the actual value of the waypointState. passing &waypointState to hasStateChanged() always results in a true even when the state hasn't changed WHY?
  bool &currentWaypointState = *waypointState;

  if (hasStateChanged(newWaypointState, currentWaypointState))
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









