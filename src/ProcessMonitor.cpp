//
// Created by Josue Figueroa on 12/13/20.
//

#include "ProcessMonitor.h"

ProcessMonitor::ProcessMonitor(float &ideal, uint16_t &interval) : ideal(ideal), interval(interval) {};

void ProcessMonitor::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(pollingTimer));
  pollingTimer->enable();
}

void ProcessMonitor::startPolling() {
  pollingTimer->enableDelayed();
}

void ProcessMonitor::stopPolling() {
  pollingTimer->disable();
}

float ProcessMonitor::getIdeal() const {
  return ideal;
}

uint16_t ProcessMonitor::getInterval() const {
  return interval;
}