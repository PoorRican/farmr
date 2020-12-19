//
// Created by Josue Figueroa on 12/12/20.
//


#include "sensor_ping.h"

SensorPing::SensorPing(const int &trigger, const int &echo)
: Sensor(0), pinTrigger(trigger), pinEcho(echo), sonar(pinTrigger,pinEcho) {
  max = 255;
  min = 0;
  samples = 0;
  for (uint_fast8_t i = 0; i < sample_size; i++) {
    levels[i] = 0;
  }
}

Sensor::SensName SensorPing::getType() const {
  return Sensor::Ping;
}

void SensorPing::init() {
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void SensorPing::update() {
#ifndef SENSORLESS_OPERATION
  levels[samples] = getPercent();

  // Update sample counter
  samples = (++samples) % sample_size;

  smooth();
#endif
}

void SensorPing::fastUpdate() {
  uint8_t w = getPercent();
  for (uint8_t i = 0; i < sample_size; i++) {
    levels[i] = w;
  }
  smooth();
}

uint8_t SensorPing::get() const {
  return level;
}

uint16_t SensorPing::getRaw() {
  return (uint16_t)sonar.ping_cm();
}

uint8_t SensorPing::getPercent() const {
  return map(level, max, min, 100, 0);
}

void SensorPing::setMax(uint16_t val) {
  max = val;
}

void SensorPing::setMin(uint16_t val) {
  min = val;
}

void SensorPing::smooth() {
  uint16_t res = 0;
  for (uint_fast8_t i = 0; i < samples; i++) {
    res += levels[i];
    level = (uint8_t)(res / sample_size);
  }
}

bool SensorPing::above_threshold() const {
  return (level > threshold) ? true : false;
}