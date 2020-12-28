//
// Created by Josue Figueroa on 12/27/20.
//

#include "UI_Reservoir.h"
#include "settings.h"

bool pumpingOn = false;
unsigned int threshold = 25;
uint16_t reservoirDuration = 5;
uint16_t reservoirInterval = 4;

void turnOnReservoirPump() {
  reservoir_pump.startPumpOnTimer();
}
void turnOffReservoirPump() {
  reservoir_pump.startPumpOnTimer();
}

result setReservoirThreshold(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Threshold set to ");
  Serial.println(threshold);
#endif
  reservoir_pump.setThreshold(threshold);
  return proceed;
}

result setReservoirDuration(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir pump duration set to ");
  Serial.println(reservoirDuration);
#endif
  reservoir_pump.setDuration(reservoirDuration);
  return proceed;
}

result setReservoirInterval(eventMask e, navNode& _nav, prompt &item) {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir pump interval set to ");
  Serial.println(reservoirInterval);
#endif
  reservoir_pump.setInterval(reservoirInterval);
  return proceed;
}