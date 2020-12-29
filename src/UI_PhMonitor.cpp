//
// Created by Josue Figueroa on 12/27/20.
//

#include "UI_PhMonitor.h"
#include "settings.h"

float currentPh = 0.0;      // Placeholder

result setIdealPh(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Ideal pH set to ");
  Serial.println(idealPh);
#endif
  ph_monitor->setIdeal(idealPh);
  return proceed;
}

result setPhPollInterval(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("pH Poll Interval set to ");
  Serial.println(phPollInterval);
#endif
  ph_monitor->setInterval(phPollInterval);
  return proceed;
}

result setPhPumpDuration(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("pH Pump Duration set to ");
  Serial.println(phPumpDuration);
#endif
  ph_monitor->setDuration(phPumpDuration);
  return proceed;
}

void turnOnPhMonitor() {
  ph_monitor->startPolling();
}
void turnOffPhMonitor() {
  ph_monitor->stopPolling();
}