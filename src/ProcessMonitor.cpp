//
// Created by Josue Figueroa on 12/13/20.
//

#include "ProcessMonitor.h"

ProcessMonitor::ProcessMonitor(float &ideal, uint16_t &interval) : ideal(ideal), interval(interval) {};

void ProcessMonitor::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(pollingTimer));
}

void ProcessMonitor::startPolling() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Starting ph monitor polling");
#endif
  pollingTimer->enableDelayed();
}

void ProcessMonitor::stopPolling() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Stopped ph monitor polling");
#endif
  pollingTimer->disable();
}

float ProcessMonitor::getIdeal() const {
  return ideal;
}

uint16_t ProcessMonitor::getInterval() const {
  return interval;
}