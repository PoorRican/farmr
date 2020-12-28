//
// Created by Josue Figueroa on 12/11/20.
//

#include "pump_water.h"

WaterPump::WaterPump(const uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorPing *sonar, Scheduler *scheduler)
: Pump(pin, duration), sonar(sonar) {
  // convert minutes to seconds
  setInterval(interval);
  setDuration(duration);

  pumpTimer = new Task(this->interval, TASK_FOREVER, startPump);
  pumpTimer->setLtsPointer(this);
  pumpOffTimer = new Task(this->duration, TASK_FOREVER, stopPump);
  pumpOffTimer->setLtsPointer(this);
}

// Setters
bool WaterPump::setDuration(const uint16_t &min) {
  if (min >= 1 && min <= 12) {
#ifdef BASIC_TESTING
    duration = min * TASK_SECOND;
#else
    duration = min * TASK_MINUTE;
#endif
    return true;
  }
  return false;
}

bool WaterPump::setInterval(const uint16_t &freq) {
  if (freq >= 1 && freq <= 12) {
#ifdef BASIC_TESTING
    interval = freq * TASK_SECOND;
#else
    interval = freq * TASK_HOUR;
#endif
    return true;
  }
  return false;
}

bool WaterPump::setThreshold(const unsigned int &val) {
  return sonar->setThreshold(val);
}

uint16_t WaterPump::getInterval() const {
  return interval;
}

bool WaterPump::aboveThreshold() const {
  return sonar->above_threshold();
}
