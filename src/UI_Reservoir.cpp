//
// Created by Josue Figueroa on 12/27/20.
//

#include "UI_Reservoir.h"
#include "settings.h"

uint8_t reservoirLevel = 0;    // placeholder

void turnOnReservoirCycle() {
  reservoir->startCycle();
}
void turnOffReservoirCycle() {
  reservoir->stopCycle();
}

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