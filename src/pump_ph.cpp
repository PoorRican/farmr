//
// Created by Josue Figueroa on 12/12/20.
//

#include "pump_ph.h"

Pump_pH::Pump_pH(const uint8_t &pin, uint16_t &duration, Scheduler* scheduler)
: Pump(pin, duration) {

  setDuration(duration);

  pumpTimer = new Task(0, TASK_ONCE, &startWatering, scheduler, true);
  pumpTimer->setLtsPointer(this);
  pumpOffTimer = new Task(duration, TASK_ONCE, &stopWatering, scheduler, true);
  pumpOffTimer->setLtsPointer(this);
};

bool Pump_pH::setDuration(const uint16_t &sec) {
  if (sec > 0 && sec < 10) {
    duration = sec * TASK_SECOND;
    return true;
  }
  return false;
}

int Pump_pH::calcNextOnTime() const {
  return 1;
}

bool Pump_pH::aboveThreshold() const {
  return true;
}

void Pump_pH::restart() {
  pumpTimer->restart();
  pumpOffTimer->restartDelayed(duration * TASK_SECOND);
}