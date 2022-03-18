//
// Created by Josue Figueroa on 12/27/20.
//

#include "ui/UI_PhMonitor.h"
#include "ui/UI_Feedback.h"
#include "settings.h"

float currentPh = 0.0;      // Placeholder

result setIdealPh(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Ideal pH set to ");
  Serial.println(idealPh);
#endif
  ph_monitor->setSetpoint(idealPh);
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
  Serial.print("pH Relay Duration set to ");
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

// Calibration Routines
result calibratePhFour(eventMask e, navNode& _nav, prompt &item) {
  SensorPH::setFour();
  nav.idleOn(alertPhCalibrated);
  return quit;
}
result calibratePhSeven(eventMask e, navNode& _nav, prompt &item) {
  SensorPH::setSeven();
  nav.idleOn(alertPhCalibrated);
  return quit;
}
result calibratePhTen(eventMask e, navNode& _nav, prompt &item) {
  SensorPH::setTen();
  nav.idleOn(alertPhCalibrated);
  return quit;
}
