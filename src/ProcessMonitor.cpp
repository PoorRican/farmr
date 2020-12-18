//
// Created by Josue Figueroa on 12/13/20.
//

#include "ProcessMonitor.h"

ProcessMonitor::ProcessMonitor(float &ideal, uint16_t &interval) : ideal(ideal), interval(interval) {};

void ProcessMonitor::startPolling() {
  pollingTimer->enable();
}

void ProcessMonitor::stopPolling() {
  pollingTimer->disable();
}