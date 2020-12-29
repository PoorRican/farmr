//
// Created by Josue Figueroa on 12/12/20.
//

#include "pump_ph.h"

Pump_pH::Pump_pH(const uint8_t &pin, uint16_t &duration, Scheduler* scheduler)
: Pump(pin, duration) {

  pumpTimer = new Task(TASK_IMMEDIATE, TASK_ONCE, startPump);
  pumpTimer->setLtsPointer(this);
  pumpOffTimer = new Task(this->duration, TASK_ONCE, stopPump);
  pumpOffTimer->setLtsPointer(this);

  setDuration(duration);
};

bool Pump_pH::setDuration(const uint16_t &sec) {
  if (sec > 0 && sec <= 10) {
    duration = sec;
    pumpOffTimer->setInterval(sec * TASK_SECOND);
    return true;
  }
  return false;
}

bool Pump_pH::aboveThreshold() const {
  return true;
}

void Pump_pH::restart() {
  pumpTimer->restart();
  pumpOffTimer->restartDelayed(duration * TASK_SECOND);
}