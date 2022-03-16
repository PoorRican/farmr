//
// Created by Josue Figueroa on 12/13/20.
//

#include "monitor/monitor.h"

Monitor::Monitor(float &ideal, uint16_t &interval) : ideal(ideal), interval(interval) {};

void Monitor::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(pollingTimer));
}

void Monitor::startPolling() {
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

void Monitor::stopPolling() {
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

float Monitor::getIdeal() const {
  return ideal;
}

uint16_t Monitor::getInterval() const {
  return interval;
}
