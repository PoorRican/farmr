//
// Created by Josue Figueroa on 12/12/20.
//

#include "pump.h"


void Pump::startPumpOnTimer() {
  if (!pumpTimer.enabled) {
    int time = calcNextOnTime();
    pumpTimer.id = Alarm.timerOnce(time, startWatering);
    pumpTimer.enabled = true;
    startPumpOffTimer();
  }
}

void Pump::stopPumpOnTimer() {
  if (pumpTimer.enabled) {
    Alarm.free(pumpTimer.id);
    pumpTimer.enabled = false;
    stopPumpOffTimer();
  }
}

void Pump::startPumpOffTimer() {
  if (!pumpOffTimer.enabled) {
    pumpOffTimer.id = Alarm.timerOnce(duration, stopWatering);
    pumpOffTimer.enabled = true;
    startPumpOnTimer();
  }
}


void Pump::stopPumpOffTimer() {
  if (pumpOffTimer.enabled) {
    Alarm.free(pumpOffTimer.id);
    pumpOffTimer.enabled = false;
  }
}


// Pump routines
OnTick_t Pump::startWatering() {
  if (sonar.above_threshold()) {
    digitalWrite(pin, HIGH);
    pumpOn = true;
    stopPumpOnTimer();
  }
}

OnTick_t Pump::stopWatering() {
  digitalWrite(pin, LOW);
  pumpOn = false;
  stopPumpOffTimer();
}


