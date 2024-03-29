//
// Created by Josue Figueroa on 12/13/20.
//

#include "logger.h"
#include "monitor/monitor.h"

Monitor::Monitor(double &ideal, uint16_t &interval, uint16_t& duration)
      : setpoint(ideal), interval(interval), duration(duration) {
  this->input = -1;

  // PID setup
  this->pid_mode = Conservative;
  this->pid = new PID((double*)(&this->input), (double*)(&this->duration), (double*)(&this->setpoint),
                      cons.Kp, cons.Ki, cons.Kp, DIRECT);
}

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
  logger.verbose((char*)&s);
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
  logger.verbose((char*)&s);
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
      logger.error("Incorrect tune set for monitor PID. How did we get here?...");
      break;
    }
  }
}

pid_tuning_mode_t Monitor::getPidMode() const {
  return pid_mode;
}

void Monitor::setAggressiveTune(double &Kp, double &Ki, double &Kd) {
#ifdef BASIC_TESTING
  logger.debug("Monitor set to aggressive tune.");
#endif

  aggr = {Kp, Ki, Kd};
}

tuning_param_t Monitor::getAggressiveTune() const {
  return aggr;
}

void Monitor::setConservativeTune(double &Kp, double &Ki, double &Kd) {
#ifdef BASIC_TESTING
  logger.debug("Monitor set to conservative tune.");
#endif

  cons = {Kp, Ki, Kd};
}

tuning_param_t Monitor::getConservativeTune() const {
  return cons;
}
