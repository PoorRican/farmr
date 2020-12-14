//
// Created by Josue Figueroa on 12/13/20.
//

#include "ProcessMonitor.h"

ProcessMonitor::ProcessMonitor(float &ideal, uint16_t &interval) : interval(interval) {
  setIdeal(ideal);
};

void ProcessMonitor::startPolling() {
  if (!pollingTimer.enabled) {
    pollingTimer.id = Alarm.timerRepeat(interval, poll);
    pollingTimer.enabled = true;
  }
}

void ProcessMonitor::stopPolling() {
  if (pollingTimer.enabled) {
    Alarm.free(pollingTimer.id);
    pollingTimer.enabled = false;
  }
}

