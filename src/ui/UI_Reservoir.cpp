//
// Created by Josue Figueroa on 12/27/20.
//

#include "ui/UI_Reservoir.h"
#include "ui/UI_Feedback.h"
#include "settings.h"

uint8_t currentLevel = 0;    // placeholder


// ===================================
// Pump mode callbacks

void continuousReservoirPumping() {
  reservoir->enableContinuous();
}
void turnOnReservoirCycle() {
  reservoir->enableCycle();
}
void turnOffReservoirCycle() {
  reservoir->disableCycle();
}


// ===================================
// Reservoir attribute callbacks

result setReservoirThreshold(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Threshold set to ");
  Serial.println(threshold);
#endif
  reservoir->setThreshold(threshold);
  return proceed;
}

result setReservoirDuration(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir pump duration set to ");
  Serial.println(reservoirDuration);
#endif
  reservoir->setDuration(reservoirDuration);
  return proceed;
}

result setReservoirInterval(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir pump interval set to ");
  Serial.println(reservoirInterval);
#endif
  reservoir->setInterval(reservoirInterval);
  return proceed;
}

// ===================================
// Calibration Routines

result calibrateReservoirMax(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Calibrated reservoir max");
#endif
  nav.idleOn(alertLevelCalibrated);
  reservoir_level->calibrateMax();
  return quit;
}

result calibrateReservoirMin(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Calibrated reservoir min");
#endif
  reservoir_level->calibrateMin();
  nav.idleOn(alertLevelCalibrated);
  return quit;
}
