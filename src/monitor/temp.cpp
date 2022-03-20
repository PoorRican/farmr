//
// Created by Josue Figueroa on 12/31/20.
//

#include "logger.h"
#include "monitor/temp.h"

MonitorTemp::MonitorTemp(double &ideal, uint16_t &interval, uint16_t &duration,
                         SensorTemp *sensor, WaterPump *pump,
                         ThermoElectricElement *heating, ThermoElectricElement *cooling)
    : Monitor(ideal, interval, duration), sensor(sensor), pump(pump),
      heatingElement(heating), coolingElement(cooling) {

  pollingTimer = new Task(this->interval, TASK_FOREVER, pollTemp);
  pollingTimer->setLtsPointer(this);

  setSetpoint(this->setpoint);
  setInterval(this->interval);
  setDuration(this->duration);

  // Final PID setup
  this->window_size = 5;      // don't exceed pumping for 5 minutes
  this->initPid();
}

Monitor::ProcessType MonitorTemp::getType() const {
  return Temperature;
}

bool MonitorTemp::setSetpoint(double &val) {
  // constrain to realistic temperatures
  // TODO: this needs to be tested
  if ((sensor->getCelsius() && val > 10 && val < 38) ||
      (!sensor->getCelsius() && val > 50 && val < 100)) {

#ifdef VERBOSE_OUTPUT
    char* s = nullptr;
    sprintf(s, "Temp monitor setpoint set to %f", val);
    logger.verbose(s);
#endif

    setpoint = val;

    return true;
  }

  char* s = nullptr;
  sprintf(s, "Incorrect duration (%f) set for water pump", val);
  logger.error(s);

  return false;
}

double MonitorTemp::getTemp() {
  sensor->update();
  this->input = sensor->get();
  return this->input;
}

bool MonitorTemp::setInterval(uint16_t &val) {
  if (val >= 15 && val <= 120) {

#ifdef VERBOSE_OUTPUT
    char* s = nullptr;
    sprintf(s, "Temp monitor polling interval set to %d", val);
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
  sprintf(s, "Incorrect polling interval (%d) set for temp monitor", val);
  logger.error(s);

  return false;
}

bool MonitorTemp::setDuration(uint16_t &val) {
  bool valid;
  valid = pump->setDuration(val);
  valid = heatingElement->setDuration(val) && valid;
  valid = coolingElement->setDuration(val) && valid;

#ifdef VERBOSE_OUTPUT
  char* s = nullptr;
  sprintf(s, "Temp monitor duration set to %d", val);
  logger.verbose(s);
#endif


  duration = val;

  return valid;
}

void MonitorTemp::poll() {
  // update temperature
  this->getTemp();
#ifdef VERBOSE_OUTPUT
  String s = "\nTemperature is " + (String)input + ((sensor->getCelsius() ? "C" : "F"));
  s = s + "Ideal is " + (String)setpoint + ((sensor->getCelsius() ? "C" : "F"));
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
    logger.verbose("Temperature is within tolerance...");
  }
#endif
}

void MonitorTemp::increase() {
#ifdef BASIC_TESTING
  logger.debug("Attempting to raise temperature");
#endif

  pump->restart();
  pump->startRelayOnTimer();

  heatingElement->restart();
  heatingElement->startRelayOnTimer();
}

void MonitorTemp::decrease() {
#ifdef BASIC_TESTING
  logger.debug("Attempting to lower temperature");
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