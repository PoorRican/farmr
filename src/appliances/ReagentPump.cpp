//
// Created by Josue Figueroa on 12/12/20.
//

#include "appliances/ReagentPump.h"
#include "logger.h"

ReagentPump::ReagentPump(const uint8_t &pin, uint16_t &duration)
: Relay(pin, duration) {

  setDuration(duration);
}

bool ReagentPump::setDuration(const uint16_t &sec) {
  if (sec > 0 && sec <= 10) {

#ifdef VERBOSE_OUTPUT
    char* s = nullptr;
    sprintf(s, "Reagent pump duration set to %d", sec);
    logger.verbose(s);
#endif

    duration = sec;
    relayOffTimer->setInterval(sec * TASK_SECOND);
    return true;
  }

  char* s = nullptr;
  sprintf(s, "Incorrect duration (%d) set for Reagent Pump", sec);
  logger.error(s);

  return false;
}

void ReagentPump::restart() {

#ifdef VERBOSE_OUTPUT
  logger.verbose("Restarting a reagent pump");
#endif

  relayTimer->restart();
  relayOffTimer->restartDelayed(duration * TASK_SECOND);
}