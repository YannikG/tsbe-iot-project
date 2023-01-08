#include "feldbahn.h"
#include "waypoint.h"
#include "trackcurrent.h"
#include "direction.h"
#include "button.h"

Waypoint stationA (new Indicator(IN_REED_STATION_A));
Waypoint curveWaypoint (new Indicator(IN_REED_CURVE));
Waypoint stationB (new Indicator(IN_REED_STATION_B));

TrackCurrent trackCurrent (OUT_TRACK_CURRENT);
Direction direction (OUT_DIRECTION_SWITCH);

Button layoutToggleButton (IN_BUTTON_START, true);
Button directionToggleButton (IN_BUTTON_DIRECTION, false);

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
}
