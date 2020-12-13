//
// Created by Josue Figueroa on 12/11/20.
//

#include "pump_water.h"


// Constructors

WaterPump::WaterPump(uint8_t &pin, uint16_t &duration, uint16_t &interval, SensorPing *sonar) : Pump(pin, duration,
                                                                                                     interval, sonar) {
  // convert minutes to seconds
  setDuration(duration);
}

WaterPump& WaterPump::operator=(const WaterPump& other) {
  pin = other.pin;
  sonar = other.sonar;
  interval = other.interval;
  duration = other.duration;
  return *this;
}


int WaterPump::calcNextOnTime() const {
  const int cycle_len = 24 / interval;  // cycle length (in hours)
  const int until_next = (24 - hour()) % cycle_len;     // hours until next cycle
  int _return = until_next ? until_next : cycle_len;  // calculate next cycle time
  return _return % 24;                                // normalize
}


// Setters
bool WaterPump::setDuration(uint16_t &min) {
  if (min >= 1 && min <= 12) {
    duration = min * 60;    // convert minutes to seconds
    return true;
  }
  return false;
}

bool WaterPump::setInterval(uint16_t &freq) {
  if (freq >= 1 && freq <= 12) {
    duration = freq;
    return true;
  }
  return false;
}
