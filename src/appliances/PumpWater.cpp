//
// Created by Josue Figueroa on 12/11/20.
//

#include "appliances/PumpWater.h"

PumpWater::PumpWater(const uint8_t &pin, uint16_t &duration)
: Relay(pin, duration) {
  setDuration(duration);
}

// Setters
bool PumpWater::setDuration(const uint16_t &min) {
  if (min >= 1 && min <= 12) {
    duration = min;
#ifdef BASIC_TESTING
    relayOffTimer->setInterval(duration * TASK_SECOND);
#else
    relayOffTimer->setInterval(duration * TASK_MINUTE);
#endif
    return true;
  }
  return false;
}

void PumpWater::restart() {
  relayTimer->restart();
#ifdef BASIC_TESTING
  relayOffTimer->restartDelayed(duration * TASK_SECOND);
#else
  relayOffTimer->restartDelayed(duration * TASK_MINUTE);
#endif
}
