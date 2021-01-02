//
// Created by Josue Figueroa on 12/31/20.
//

#include "scheduler.h"
#include "MonitorTemp.h"

MonitorTemp::MonitorTemp(float &ideal, uint16_t &interval, uint16_t &duration, SensorTemp &sensor, PumpWater &pump,
                         ThermoElectricElement &heating, ThermoElectricElement &cooling)
    : ProcessMonitor(ideal, interval), duration(duration), sensor(sensor), pump(pump),
      heatingElement(heating), coolingElement(cooling) {

  pollingTimer = new Task(this->interval, TASK_FOREVER, pollTemp);
  pollingTimer->setLtsPointer(this);

  setInterval(this->interval);
  setDuration(this->duration);
}

ProcessMonitor::ProcessType MonitorTemp::getType() const {
  return Temperature;
}

bool MonitorTemp::setIdeal(float &val) {
  // constrain to realistic temperatures
  // TODO: this needs to be tested
  if ((sensor.getCelsius() && val > 10 && val < 38) ||
      (!sensor.getCelsius() && val > 50 && val < 100)) {
    ideal = val;
    return true;
  }
  return false;
}

float MonitorTemp::getCurrentTemp() const {
  sensor.update();
  return sensor.get();
}

bool MonitorTemp::setInterval(uint16_t &val) {
  if (val >= 15 && val <= 120) {
    interval = val;
#ifdef BASIC_TESTING
    pollingTimer->setInterval(interval * TASK_SECOND);
#else
    pollingTimer->setInterval(interval * TASK_MINUTE);
#endif
  }
}

bool MonitorTemp::setDuration(uint16_t &val) {
  bool valid;
  valid = pump.setDuration(val);
  valid = heatingElement.setDuration(val) && valid;
  valid = coolingElement.setDuration(val) && valid;
  return valid;
}

void MonitorTemp::poll() {
  sensor.update();
  float temp = sensor.get();
#ifdef VERBOSE_OUTPUT
  // assuming String operations are quicker than multiple Serial operations
  String s = "\nTemperature is " + (String)temp + ((sensor.getCelsius() ? "C" : "F"));
  s = s + "Ideal is " + (String)ideal + ((sensor.getCelsius() ? "C" : "F"));
  Serial.println(s);
#endif
  if (temp < ideal && (ideal - temp) >= tolerance) {
    increase();
  }
  else if (temp > ideal && (temp - ideal) >= tolerance) {
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
  pump.restart();
  pump.startPumpOnTimer();

  heatingElement.restart();
  heatingElement.startPumpOnTimer();
}

void MonitorTemp::decrease() {
#ifdef VERBOSE_OUTPUT
  Serial.println("Attempting to lower temperature");
#endif
  pump.restart();
  pump.startPumpOnTimer();

  coolingElement.restart();
  coolingElement.startPumpOnTimer();
}

void pollTemp() {
  Task& t = ts.currentTask();
  MonitorTemp& m = *((MonitorTemp*) t.getLtsPointer());
  m.poll();
}