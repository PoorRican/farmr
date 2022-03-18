//
// Created by Josue Figueroa on 12/31/20.
//

#include "monitor/temp.h"

MonitorTemp::MonitorTemp(float &ideal, uint16_t &interval, uint16_t &duration,
                         SensorTemp *sensor, WaterPump *pump,
                         ThermoElectricElement *heating, ThermoElectricElement *cooling)
    : Monitor(ideal, interval, duration), sensor(sensor), pump(pump),
      heatingElement(heating), coolingElement(cooling) {

  pollingTimer = new Task(this->interval, TASK_FOREVER, pollTemp);
  pollingTimer->setLtsPointer(this);

  setIdeal(this->ideal);
  setInterval(this->interval);
  setDuration(this->duration);

  this->temperature = -1;

  // PID setup
  this->pid_mode = Conservative;
  this->pid = new PID((double*)(&this->temperature), (double*)(&this->duration), (double*)(&this->ideal),
                      cons.Kp, cons.Ki, cons.Kd, DIRECT);

  this->window_size = 5;      // don't exceed pumping for 5 minutes
  this->initPid();
}

Monitor::ProcessType MonitorTemp::getType() const {
  return Temperature;
}

bool MonitorTemp::setIdeal(float &val) {
  // constrain to realistic temperatures
  // TODO: this needs to be tested
  if ((sensor->getCelsius() && val > 10 && val < 38) ||
      (!sensor->getCelsius() && val > 50 && val < 100)) {
    ideal = val;
    return true;
  }
  return false;
}

float MonitorTemp::getTemp() {
  sensor->update();
  this->temperature = sensor->get();
  return this->temperature;
}

bool MonitorTemp::setInterval(uint16_t &val) {
  if (val >= 15 && val <= 120) {
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

bool MonitorTemp::setDuration(uint16_t &val) {
  bool valid;
  valid = pump->setDuration(val);
  valid = heatingElement->setDuration(val) && valid;
  valid = coolingElement->setDuration(val) && valid;

  duration = val;

  return valid;
}

void MonitorTemp::poll() {
  // update temperature
  this->getTemp();
#ifdef VERBOSE_OUTPUT
  String s = "\nTemperature is " + (String)temperature + ((sensor->getCelsius() ? "C" : "F"));
  s = s + "Ideal is " + (String)ideal + ((sensor->getCelsius() ? "C" : "F"));
  Serial.println(s);
#endif

  pid->Compute();

  if (temperature < ideal && (ideal - temperature) >= tolerance) {
    increase();
  }
  else if (temperature > ideal && (temperature - ideal) >= tolerance) {
    decrease();
  }
#ifdef VERBOSE_OUTPUT
  else {
    Serial.println("Temperature is within tolerance...");
  }
#endif
}

void MonitorTemp::increase() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Attempting to raise temperature");
#endif
  pump->restart();
  pump->startRelayOnTimer();

  heatingElement->restart();
  heatingElement->startRelayOnTimer();
}

void MonitorTemp::decrease() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Attempting to lower temperature");
#endif
  pump->restart();
  pump->startRelayOnTimer();

  coolingElement->restart();
  coolingElement->startRelayOnTimer();
}

void pollTemp() {
  Task& t = ts.currentTask();
  MonitorTemp& m = *((MonitorTemp*) t.getLtsPointer());
  m.poll();
}