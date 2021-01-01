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
  String s = "Starting ";
  switch (this->getType()) {
    case pH: {
      s += "pH";
      break;
    }

    case Nitrobacter: {
      s += "Nitrobacter";
      break;
    }

    case Temperature: {
      s += "Temp";
      break;
    }

    case Filtration: {
      s += "Filter";
      break;
    }

    default: {
      break;
    }
  }
  s += " monitor polling...";
  Serial.print(s);
#endif
  pollingTimer->enableDelayed();
}

void ProcessMonitor::stopPolling() {
#ifdef VERBOSE_OUTPUT
  String s = "Stopped ";
  switch (this->getType()) {
    case pH: {
      s += "pH";
      break;
    }

    case Nitrobacter: {
      s += "Nitrobacter";
      break;
    }

    case Temperature: {
      s += "Temp";
      break;
    }

    case Filtration: {
      s += "Filter";
      break;
    }

    default: {
      break;
    }
  }
  s += " monitor polling...";
  Serial.print(s);
#endif
  pollingTimer->disable();
}

float ProcessMonitor::getIdeal() const {
  return ideal;
}

uint16_t ProcessMonitor::getInterval() const {
  return interval;
}