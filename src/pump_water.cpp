//
// Created by Josue Figueroa on 12/11/20.
//

#include "pump_water.h"

WaterPump::WaterPump(const uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorLevel *level, Scheduler *scheduler)
: Pump(pin, duration), level(level) {
  pumpTimer = new Task(this->interval, TASK_FOREVER, startPump);
  pumpTimer->setLtsPointer(this);
  pumpOffTimer = new Task(this->duration, TASK_ONCE, stopPump);
  pumpOffTimer->setLtsPointer(this);

  setInterval(interval);
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

bool WaterPump::setInterval(const uint16_t &freq) {
  if (freq >= 1 && freq <= 12) {
    interval = freq;
#ifdef BASIC_TESTING
    pumpTimer->setInterval(interval * TASK_SECOND);
#else
    pumpTimer->setInterval(interval * TASK_HOUR);
#endif
    return true;
  }
  return false;
}

bool WaterPump::setThreshold(const uint8_t &val) {
  return level->setThreshold(val);
}

uint16_t WaterPump::getInterval() const {
  return interval;
}

bool WaterPump::aboveThreshold() const {
  return level->aboveThreshold();
}
