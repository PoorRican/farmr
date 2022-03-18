//
// Created by Josue Figueroa on 12/13/20.
//

#include "monitor/monitor.h"

Monitor::Monitor(double &ideal, uint16_t &interval, uint16_t& duration)
      : setpoint(ideal), interval(interval), duration(duration) {}

void Monitor::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(pollingTimer));
}

double Monitor::getSetpoint() const {
  return setpoint;
}

uint16_t Monitor::getInterval() const {
  return interval;
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


// =====================
// PID Methods

void Monitor::initPid() {
  // normalize output
  pid->SetOutputLimits(0, window_size);

  // is this necessary?
  pid->SetMode(AUTOMATIC);
}

void Monitor::switchPidMode(pid_tuning_mode_t tune) {
  switch (tune) {
    case Aggressive: {
      pid->SetTunings(aggr.Kp, aggr.Ki, aggr.Kd);
      break;
    }
    case Conservative: {
      pid->SetTunings(cons.Kp, cons.Ki, cons.Kd);
      break;
    }
    default: {
      // TODO: log error. How did we get here?
      break;
    }
  }
}

pid_tuning_mode_t Monitor::getPidMode() const {
  return pid_mode;
}

void Monitor::setAggressiveTune(double &Kp, double &Ki, double &Kd) {
  aggr = {Kp, Ki, Kd};
}

tuning_param_t Monitor::getAggressiveTune() const {
  return aggr;
}

void Monitor::setConservativeTune(double &Kp, double &Ki, double &Kd) {
  cons = {Kp, Ki, Kd};
}

tuning_param_t Monitor::getConservativeTune() const {
  return cons;
}
