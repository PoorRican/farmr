//
// Created by Josue Figueroa on 12/11/20.
//

#include "logger.h"
#include "appliances/WaterPump.h"

WaterPump::WaterPump(const uint8_t &pin, uint16_t &duration)
: Relay(pin, duration) {

  setDuration(duration);
}

// Setters
bool WaterPump::setDuration(const uint16_t &val) {
  if (val >= 1 && val <= 12) {

#ifdef VERBOSE_OUTPUT
    char* s = nullptr;
    sprintf(s, "Thermoelectric element duration set to %d", val);
    logger.verbose(s);
#endif

    duration = val;
    
#ifdef BASIC_TESTING
    relayOffTimer->setInterval(duration * TASK_SECOND);
#else
    relayOffTimer->setInterval(duration * TASK_MINUTE);
#endif
    
    return true;
  }

  char* s = nullptr;
  sprintf(s, "Incorrect duration (%d) set for water pump", val);
  logger.error(s);
  
  return false;
}

void WaterPump::restart() {

#ifdef VERBOSE_OUTPUT
  logger.verbose("Restarting a thermoelectric element");
#endif

  relayTimer->restart();
  
#ifdef BASIC_TESTING
  relayOffTimer->restartDelayed(duration * TASK_SECOND);
#else
  relayOffTimer->restartDelayed(duration * TASK_MINUTE);
#endif
}
