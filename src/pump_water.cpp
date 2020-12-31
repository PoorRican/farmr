//
// Created by Josue Figueroa on 12/11/20.
//

#include "pump_water.h"

WaterPump::WaterPump(const uint8_t &pin, uint16_t &duration)
: Pump(pin, duration) {
  pumpTimer = new Task(TASK_IMMEDIATE, TASK_ONCE, startPump);
  pumpTimer->setLtsPointer(this);
  pumpOffTimer = new Task(this->duration, TASK_ONCE, stopPump);
  pumpOffTimer->setLtsPointer(this);

  setDuration(duration);

}

// Setters
bool WaterPump::setDuration(const uint16_t &min) {
  if (min >= 1 && min <= 12) {
    duration = min;
#ifdef BASIC_TESTING
    pumpOffTimer->setInterval(duration * TASK_SECOND);
#else
    pumpOffTimer->setInterval(duration * TASK_MINUTE);
#endif
    return true;
  }
  return false;
}

bool WaterPump::aboveThreshold() const {
  return true;
}

void WaterPump::restart() {
  pumpTimer->restart();
#ifdef BASIC_TESTING
  pumpOffTimer->restartDelayed(duration * TASK_SECOND);
#else
  pumpOffTimer->restartDelayed(duration * TASK_MINUTE);
#endif
}
