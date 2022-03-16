//
// Created by Josue Figueroa on 12/13/20.
//

#include "scheduler.h"
#include "monitor/ph.h"

MonitorPh::MonitorPh(float &ideal, uint16_t &interval, SensorPH &sensor, ReagentPump &acidPump, ReagentPump &basePump)
    : Monitor(ideal, interval), sensor(sensor), acidPump(acidPump), basePump(basePump) {

  pollingTimer = new Task(this->interval, TASK_FOREVER, pollPH);
  pollingTimer->setLtsPointer(this);

  setIdeal(ideal);
  setInterval(interval);
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

float MonitorPh::getCurrentPh() const {
  sensor.update();
  return sensor.get();
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
  bool _return;
  _return = acidPump.setDuration(val);
  if (_return) {
    _return = basePump.setDuration(val);
  }
  else {
    basePump.setDuration(val);
  }
  return _return;
}

void MonitorPh::poll() {
  sensor.update();
  float _ph = sensor.get();
  // NOTE: avr `abs` does not seem to support float types
  // TODO: implement PID
#ifdef VERBOSE_OUTPUT
  String s = "\npH is " + (String)_ph + ". Ideal is " + (String)ideal;
  Serial.println(s);
#endif
  if (_ph < ideal && (ideal - _ph) >= tolerance) {
    increase();
  }
  else if (_ph > ideal && (_ph - ideal) >= tolerance) {
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
  basePump.restart();
  basePump.startRelayOnTimer();
}

void MonitorPh::decrease() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Attempting to decrease pH");
#endif
  acidPump.restart();
  acidPump.startRelayOnTimer();
}

void pollPH() {
  Task& t = ts.currentTask();
  MonitorPh& p = *((MonitorPh*) t.getLtsPointer());
  p.poll();
}