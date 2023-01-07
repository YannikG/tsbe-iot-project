#include "feldbahn.h"
#include "waypoint.h"

Waypoint stationA (new Indicator(IN_REED_STATION_A));
Waypoint curveWaypoint (new Indicator(IN_REED_CURVE));
Waypoint stationB (new Indicator(IN_REED_STATION_B));

void setup() {
  Serial.begin(9600);

  Serial.println(F("done setup!"));
}

void loop() {
  stationA.onLoop();
  stationB.onLoop();
  curveWaypoint.onLoop();

  Serial.flush();
  Serial.println("Station A is occupied: ");
  Serial.println(stationA.isOccupied());

  Serial.println("Station B is occupied: ");
  Serial.println(stationB.isOccupied());

  Serial.println("Curve Waypoint is occupied: ");
  Serial.println(curveWaypoint.isOccupied());

  delay(200);
}
