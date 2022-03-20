//
// Created by Josue Figueroa on 12/13/20.
//

#include "logger.h"
#include "monitor/ph.h"

MonitorPh::MonitorPh(double &ideal, uint16_t &interval, uint16_t &duration,
                     SensorPH *sensor, ReagentPump *acidPump, ReagentPump *basePump)
    : Monitor(ideal, interval, duration), sensor(sensor), acidPump(acidPump), basePump(basePump) {

  pollingTimer = new Task(this->interval, TASK_FOREVER, pollPH);
  pollingTimer->setLtsPointer(this);

  setSetpoint(this->setpoint);
  setInterval(this->interval);
  setDuration(this->duration);

  // Final PID setup
  this->window_size = 5;      // don't exceed pumping buffer for 5 seconds
  this->initPid();
}

Monitor::ProcessType MonitorPh::getType() const {
  return pH;
}

bool MonitorPh::setSetpoint(double &val) {
  if (val >= 1.0 && val <= 14.0 ) {
    setpoint = val;

#ifdef VERBOSE_OUTPUT
    char* s = nullptr;
    sprintf(s, "pH Monitor setpoint set to %f", val);
    logger.error(s);
#endif

    return true;
  }

  char* s = nullptr;
  sprintf(s, "Incorrect setpoint (%f) set for pH Monitor", val);
  logger.error(s);

  return false;
}

double MonitorPh::getPh() {
  sensor->update();
  this->input = sensor->get();
  return this->input;
}

bool MonitorPh::setInterval(uint16_t &val) {
  if (val >= 1 && val <= 120 ) {

#ifdef VERBOSE_OUTPUT
    char* s = nullptr;
    sprintf(s, "pH Monitor polling interval set to %d", val);
    logger.verbose(s);
#endif

    interval = val;

#ifdef BASIC_TESTING
    pollingTimer->setInterval(interval * TASK_SECOND);
#else
    pollingTimer->setInterval(interval * TASK_MINUTE);
#endif

    return true;
  }

  char* s = nullptr;
  sprintf(s, "Incorrect polling interval (%d) set for pH monitor", val);
  logger.error(s);

  return false;
}

bool MonitorPh::setDuration(uint16_t &val) {
  bool valid;
  valid = acidPump->setDuration(val);
  valid = basePump->setDuration(val) && valid;

#ifdef VERBOSE_OUTPUT
  char* s = nullptr;
  sprintf(s, "pH monitor duration set to %d", val);
  logger.verbose(s);
#endif

  duration = val;

  return valid;
}

void MonitorPh::poll() {
  // update ph
  this->getPh();

#ifdef VERBOSE_OUTPUT
  String s = "\npH is " + (String)input + ". Ideal is " + (String)setpoint;
  logger.verbose((char*)&s);
#endif

  // Compute PID
  double gap = abs(input - setpoint);
  if (gap <= gap_threshold) {
    switchPidMode(pid_tuning_mode_t::Conservative);
  }
  else {
    switchPidMode(pid_tuning_mode_t::Aggressive);
  }
  pid->Compute();

  if (input < setpoint && (setpoint - input) >= tolerance) {
    increase();
  }
  else if (input > setpoint && (input - setpoint) >= tolerance) {
    decrease();
  }
#ifdef VERBOSE_OUTPUT
  else {
    logger.verbose("pH is within tolerance...");
  }
#endif
}

void MonitorPh::increase() {

#ifdef BASIC_TESTING
  logger.debug("Attempting to increase pH");
#endif

  basePump->restart();
  basePump->startRelayOnTimer();
}

void MonitorPh::decrease() {

#ifdef BASIC_TESTING
  logger.debug("Attempting to decrease pH");
#endif

  acidPump->restart();
  acidPump->startRelayOnTimer();
}

void pollPH() {
  Task& t = ts.currentTask();
  MonitorPh& p = *((MonitorPh*) t.getLtsPointer());
  p.poll();
}