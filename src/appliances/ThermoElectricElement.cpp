//
// Created by Josue Figueroa on 12/31/20.
//

#include "logger.h"
#include "appliances/ThermoElectricElement.h"

ThermoElectricElement::ThermoElectricElement(const uint8_t &pin, uint16_t &duration)
    : Relay(pin, duration) {
  setDuration(duration);
}

// Setters
bool ThermoElectricElement::setDuration(const uint16_t &min) {
  if (min >= 1 && min <= 20) {

#ifdef VERBOSE_OUTPUT
    char* s = nullptr;
    sprintf(s, "Thermoelectric element duration set to %d", min);
    logger.verbose(s);
#endif

    duration = min;

#ifdef BASIC_TESTING
    relayOffTimer->setInterval(duration * TASK_SECOND);
#else
    relayOffTimer->setInterval(duration * TASK_MINUTE);
#endif

    return true;
  }

  char* s = nullptr;
  sprintf(s, "Incorrect duration (%d) set for Thermoelectric element", min);
  logger.error(s);

  return false;
}

void ThermoElectricElement::restart() {

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
