//
// Created by Josue Figueroa on 12/12/20.
//

#include "pump_ph.h"

Pump_pH::Pump_pH(uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorPing *sonar)
: Pump(pin, duration, interval, sonar) {

  setInterval(interval);
  setDuration(duration);

  pumpTimer = new Task(duration, TASK_ONCE, &startWatering, &ts);
  pumpTimer->setLtsPointer(this);
  pumpOffTimer = new Task(duration, TASK_ONCE, &stopWatering, &ts);
  pumpOffTimer->setLtsPointer(this);
};

bool Pump_pH::setDuration(uint16_t &sec) {
  if (sec > 0 && sec < 10) {
    duration = sec;
    return true;
  }
  return false;
}

bool Pump_pH::setInterval(uint16_t &sec) {
  if (sec >= 10 && sec <= 120 ) {
    interval = sec;
    return true;
  }
  return false;
}

int Pump_pH::calcNextOnTime() const {
  return 1;
}