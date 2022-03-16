//
// Created by Josue Figueroa on 12/30/20.
//

#include "reservoir.h"

Reservoir::Reservoir(const uint16_t &interval, const uint8_t &threshold, WaterPump *waterPump, SensorDistance *sensorLevel)
: interval(interval), threshold(threshold), pump(waterPump), level(sensorLevel) {
  enabled = false;

  cycleTimer = new Task(interval, TASK_FOREVER, cycleWater);
  cycleTimer->setLtsPointer(this);

  setInterval(interval);
}

void Reservoir::enableCycleTimer() {
  enabled = true;
}

void Reservoir::disableCycleTimer() {
  enabled = false;
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

void Reservoir::runCycle() {
  if (aboveThreshold()) {
    pump->restart();
    pump->startRelayOnTimer();
  }
}

void Reservoir::addTasks(Scheduler &scheduler) {
  scheduler.addTask(*(cycleTimer));
}
void Reservoir::startCycle() {
  cycleTimer->enableDelayed();
}

void Reservoir::stopCycle() {
  cycleTimer->disable();
  // TODO: immediately stop pumps
}

bool Reservoir::aboveThreshold() const {
  return level->aboveThreshold();
}

void cycleWater() {
  Task& t = ts.currentTask();
  Reservoir& r = *((Reservoir*) t.getLtsPointer());

  r.runCycle();

#ifdef BASIC_TESTING
  Serial.println("Began reservoir water cycle");
#endif
}