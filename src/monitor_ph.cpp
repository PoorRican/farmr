//
// Created by Josue Figueroa on 12/13/20.
//

#include "monitor_ph.h"

pHMonitor::pHMonitor(float &ideal, uint16_t &interval, SensorPH &sensor, Pump_pH &acidPump, Pump_pH &basePump)
: ProcessMonitor(ideal, interval), sensor(sensor), acidPump(acidPump), basePump(basePump) {
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

bool pHMonitor::setInterval(uint16_t &val) {
  if (val >= 5 && val <= 120 ) {
    ideal = val;
    return true;
  }
  return false;
}

OnTick_t pHMonitor::poll() {
  sensor.update();
  float _ph = sensor.get();
  // NOTE: avr `abs` does not seem to support float types
  // TODO: add PID
  if (_ph < ideal && (ideal - _ph) <= tolerance) {
    increase();
  }
  else if (_ph > ideal && (_ph - ideal) <= tolerance) {
    decrease();
  }
}

void pHMonitor::increase() {
  basePump.startPumpOnTimer();
}

void pHMonitor::decrease() {
  acidPump.startPumpOnTimer();
}