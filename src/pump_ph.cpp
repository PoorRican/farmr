//
// Created by Josue Figueroa on 12/12/20.
//

#include "pump_ph.h"


Pump_pH& Pump_pH::operator=(const Pump_pH &other) {
  pin = other.pin;
  sonar = other.sonar;
  interval = other.interval;
  duration = other.duration;
  return *this;
}

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