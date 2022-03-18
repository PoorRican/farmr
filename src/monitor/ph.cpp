//
// Created by Josue Figueroa on 12/13/20.
//

#include "monitor/ph.h"

MonitorPh::MonitorPh(float &ideal, uint16_t &interval, uint16_t &duration,
                     SensorPH *sensor, ReagentPump *acidPump, ReagentPump *basePump)
    : Monitor(ideal, interval, duration), sensor(sensor), acidPump(acidPump), basePump(basePump) {

  pollingTimer = new Task(this->interval, TASK_FOREVER, pollPH);
  pollingTimer->setLtsPointer(this);

  setIdeal(this->ideal);
  setInterval(this->interval);
  setDuration(this->duration);

  this->ph = -1;

  // PID setup
  this->pid_mode = Conservative;
  this->pid = new PID((double*)(&this->ph), (double*)(&this->duration), (double*)(&this->ideal),
                      cons.Kp, cons.Ki, cons.Kp, DIRECT);


  this->window_size = 5;      // don't exceed pumping buffer for 5 seconds
  this->initPid();
}

Monitor::ProcessType MonitorPh::getType() const {
  return pH;
}

bool MonitorPh::setIdeal(float &val) {
  if (val >= 1.0 && val <= 14.0 ) {
    ideal = val;
    return true;
  }
  return false;
}

float MonitorPh::getPh() {
  sensor->update();
  this->ph = sensor->get();
  return this->ph;
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
  String s = "\npH is " + (String)ph + ". Ideal is " + (String)ideal;
  Serial.println(s);
#endif

  // Compute PID
  double gap = abs(ph-ideal);
  if (gap <= gap_threshold) {
    switchPidMode(pid_tuning_mode_t::Conservative);
  }
  else {
    switchPidMode(pid_tuning_mode_t::Aggressive);
  }
  pid->Compute();

  if (ph < ideal && (ideal - ph) >= tolerance) {
    increase();
  }
  else if (ph > ideal && (ph - ideal) >= tolerance) {
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