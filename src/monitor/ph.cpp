//
// Created by Josue Figueroa on 12/13/20.
//

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
    return true;
  }
  return false;
}

double MonitorPh::getPh() {
  sensor->update();
  this->input = sensor->get();
  return this->input;
}

bool MonitorPh::setInterval(uint16_t &val) {
  if (val >= 1 && val <= 120 ) {
    interval = val;
#ifdef BASIC_TESTING
    pollingTimer->setInterval(interval * TASK_SECOND);
#else
    pollingTimer->setInterval(interval * TASK_MINUTE);
#endif
    return true;
  }
  return false;
}

bool MonitorPh::setDuration(uint16_t &val) {
  bool valid;
  valid = acidPump->setDuration(val);
  valid = basePump->setDuration(val) && valid;

  duration = val;

  return valid;
}

void MonitorPh::poll() {
  // update ph
  this->getPh();

#ifdef VERBOSE_OUTPUT
  String s = "\npH is " + (String)input + ". Ideal is " + (String)setpoint;
  Serial.println(s);
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
    Serial.println("pH is within tolerance...");
  }
#endif
}

void MonitorPh::increase() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Attempting to increase pH");
#endif
  basePump->restart();
  basePump->startRelayOnTimer();
}

void MonitorPh::decrease() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Attempting to decrease pH");
#endif
  acidPump->restart();
  acidPump->startRelayOnTimer();
}

void pollPH() {
  Task& t = ts.currentTask();
  MonitorPh& p = *((MonitorPh*) t.getLtsPointer());
  p.poll();
}