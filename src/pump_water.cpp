//
// Created by Josue Figueroa on 12/11/20.
//

#include "pump_water.h"

WaterPump::WaterPump(const uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorPing *sonar, Scheduler *scheduler)
: Pump(pin, duration),sonar(sonar) {
  // convert minutes to seconds
  setInterval(interval);
  setDuration(duration);

  pumpTimer = new Task(duration, TASK_FOREVER, &startWatering, scheduler, true);
  pumpTimer->setLtsPointer(this);
  pumpOffTimer = new Task(duration, TASK_FOREVER, &stopWatering, scheduler, true);
  pumpOffTimer->setLtsPointer(this);
}

int WaterPump::calcNextOnTime() const {
  const int cycle_len = 24 / interval;  // cycle length (in hours)
  const int until_next = (24 - hour()) % cycle_len;     // hours until next cycle
  int _return = until_next ? until_next : cycle_len;  // calculate next cycle time
  return _return % 24;                                // normalize
}

// Setters
bool WaterPump::setDuration(const uint16_t &min) {
  if (min >= 1 && min <= 12) {
    duration = min * TASK_MINUTE;    // convert minutes to seconds
    return true;
  }
  return false;
}

bool WaterPump::setInterval(const uint16_t &freq) {
  if (freq >= 1 && freq <= 12) {
    duration = freq * TASK_HOUR;
    return true;
  }
  return false;
}

uint16_t WaterPump::getInterval() const {
  return interval;
}

bool WaterPump::aboveThreshold() const {
  return sonar->above_threshold();
}
