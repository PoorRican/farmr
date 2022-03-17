//
// Created by Josue Figueroa on 12/30/20.
//

#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include "reservoir.h"

Reservoir::Reservoir(const uint16_t &interval, const uint8_t &threshold, WaterPump *waterPump, SensorDistance *sensorLevel)
: interval(interval), threshold(threshold), pump(waterPump), level(sensorLevel) {

  mode = Off;

  cycleTimer = new Task(interval, TASK_FOREVER, cycleWater);
  cycleTimer->setLtsPointer(this);

  setInterval(interval);
}

bool Reservoir::setDuration(const uint16_t &min) {
  return pump->setDuration(min);
}

uint16_t Reservoir::getDuration() const {
  return pump->getDuration();
}

bool Reservoir::setInterval(const uint16_t &val) {
  if (val >= 1 && val <= 12) {
    interval = val;
#ifdef BASIC_TESTING
    cycleTimer->setInterval(interval * TASK_SECOND);
#else
    cycleTimer->setInterval(interval * TASK_HOUR);
#endif
    return true;
  }
  return false;
}

bool Reservoir::setThreshold(const uint8_t &val) {
  return level->setThreshold(val);
}

uint16_t Reservoir::getInterval() const {
  return interval;
}

uint8_t Reservoir::getThreshold() const {
  return threshold;
}

uint8_t Reservoir::getCurrentLevel() const {
  level->update();
  return level->get();
}

void Reservoir::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(cycleTimer));
}

Reservoir::PumpMode Reservoir::getPumpMode() const {
  return mode;
}

void Reservoir::runCycleNow() {
  if (aboveThreshold()) {
    pump->restart();
    pump->startRelayOnTimer();
    mode = PumpMode::Cycle;
  }
}

void Reservoir::enableContinuous() {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir pump set to continuous operation.");
#endif
  cycleTimer->disable();
  pump->energize();
  mode = PumpMode::Continuous;
}

void Reservoir::enableCycle() {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir cycle enabled.");
#endif
  cycleTimer->enableDelayed();
  mode = PumpMode::Cycle;
}

void Reservoir::disableCycle() {
#ifdef VERBOSE_OUTPUT
  Serial.print("Reservoir cycle disabled. Pump turned off.");
#endif
  cycleTimer->disable();
  pump->deenergize();
  mode = PumpMode::Off;
}

bool Reservoir::aboveThreshold() const {
  return level->aboveThreshold();
}

void cycleWater() {
  Task& t = ts.currentTask();
  Reservoir& r = *((Reservoir*) t.getLtsPointer());

  r.runCycleNow();

#ifdef VERBOSE_OUTPUT
  Serial.println("Began reservoir water cycle");
#endif
}