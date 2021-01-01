//
// Created by Josue Figueroa on 12/31/20.
//

#include "ui/UI_TempMonitor.h"
#include "settings.h"

float currentTemp = 0.0;  // placeholder

void turnOnTempMonitor() {
  monitor_temp->startPolling();
}
void turnOffTempMonitor() {
  monitor_temp->stopPolling();
}

result setIdealTemp(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Ideal temperature set to ");
  Serial.println(idealTemp);
#endif
  monitor_temp->setIdeal(idealTemp);
  return proceed;
}

result setTempInterval(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Temperature Monitor Poll Interval set to ");
  Serial.println(tempInterval);
#endif
  monitor_temp->setInterval(tempInterval);
  return proceed;
}

result setTempDuration(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Temperature Monitor Pump/Thermoelectric Element Duration set to ");
  Serial.println(tempDuration);
#endif
  monitor_temp->setDuration(tempDuration);
  return proceed;
}
