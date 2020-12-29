//
// Created by Josue Figueroa on 12/13/20.
//

#include "scheduler.h"
#include "monitor_ph.h"

pHMonitor::pHMonitor(float &ideal, uint16_t &interval, SensorPH &sensor, Pump_pH &acidPump, Pump_pH &basePump, Scheduler *scheduler)
: ProcessMonitor(ideal, interval), sensor(sensor), acidPump(acidPump), basePump(basePump) {

  pollingTimer = new Task(this->interval, TASK_FOREVER, pollPH);
  pollingTimer->setLtsPointer(this);

  setIdeal(ideal);
  setInterval(interval);
}

ProcessMonitor::ProcessType pHMonitor::getType() const {
  return pH;
}

bool pHMonitor::setIdeal(float &val) {
  if (val >= 1.0 && val <= 14.0 ) {
    ideal = val;
    return true;
  }
  return false;
}

float pHMonitor::getCurrentPh() const {
  return sensor.get();
}

bool pHMonitor::setInterval(uint16_t &val) {
  if (val >= 5 && val <= 120 ) {
    interval = val;
    pollingTimer->setInterval(interval * TASK_SECOND);
    return true;
  }
  return false;
}

bool pHMonitor::setDuration(uint16_t &val) {
  bool _return = true;
  _return = acidPump.setDuration(val);
  if (_return) {
    _return = basePump.setDuration(val);
  }
  else {
    basePump.setDuration(val);
  }
  return _return;
}

void pHMonitor::poll() {
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

void pHMonitor::increase() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Attempting to increase pH");
#endif
  basePump.restart();
  basePump.startPumpOnTimer();
}

void pHMonitor::decrease() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Attempting to decrease pH");
#endif
  acidPump.restart();
  acidPump.startPumpOnTimer();
}

void pollPH() {
  Task& t = ts.currentTask();
  pHMonitor& p = *((pHMonitor*) t.getLtsPointer());
  p.poll();
}