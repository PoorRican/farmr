//
// Created by Josue Figueroa on 12/12/20.
//

#include "appliances/PumpPh.h"

PumpPh::PumpPh(const uint8_t &pin, uint16_t &duration)
: Relay(pin, duration) {

  setDuration(duration);
};

bool PumpPh::setDuration(const uint16_t &sec) {
  if (sec > 0 && sec <= 10) {
    duration = sec;
    relayOffTimer->setInterval(sec * TASK_SECOND);
    return true;
  }
  return false;
}

void PumpPh::restart() {
  relayTimer->restart();
  relayOffTimer->restartDelayed(duration * TASK_SECOND);
}