//
// Created by Josue Figueroa on 12/12/20.
//


#include "sensor_ping.h"

SensorPing::SensorPing(const int trigger, const int echo)
: Sensor(0), pinTrigger(trigger), pinEcho(echo), sonar(pinTrigger,pinEcho) {
  max = 255;
  min = 0;
  samples = 0;
  for (uint_fast8_t i = 0; i < sample_size; i++) {
    levels[i] = 0;
  }
}

SensorPing::SensorPing(const SensorPing &other) : Sensor(other), sonar(other.sonar) {
  pinTrigger = other.pinTrigger;
  pinEcho = other.pinEcho;
  samples = other.samples;
  for (uint_fast8_t i = 0; i < sample_size; i++) {
    levels[i] = other.levels[i];
  }
  level = other.level;
}

SensorPing& SensorPing::operator=(const SensorPing &other) {
  pinTrigger = other.pinTrigger;
  pinEcho = other.pinEcho;
  samples = other.samples;
  for (uint8_t i = 0; i < sample_size; i++) {
    levels[i] = other.levels[i];
  }
  level = other.level;
  return *this;
}

SensorPing::~SensorPing() = default;

Sensor::SensName SensorPing::getType() const {
  return Sensor::Ping;
}

void SensorPing::init() {
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void SensorPing::update() {
  levels[samples] = getPercent();

  // Update sample counter
  samples = (++samples) % sample_size;

  smooth();
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

uint8_t SensorPing::getPercent() {
  unsigned int duration, distance;
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinTrigger, LOW);
  // calculate duration. Timeout of .5s
  duration = pulseIn(pinEcho, HIGH, 500000);
  distance = (duration / 29);
  distance = constrain(distance, max, min);
  return map(distance, max, min, 100, 0);
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