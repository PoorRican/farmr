//
// Created by Josue Figueroa on 12/25/20.
//

#ifndef FARMR_PINS_H
#define FARMR_PINS_H

#include "Arduino.h"

struct {
  const uint8_t acidPin = 52;
  const uint8_t basePin = 53;
  const uint8_t sensorPin = 2;
} ph_monitor_t;

struct {
  const uint8_t trigger = 3;
  const uint8_t echo = 4;
  const uint8_t pin = 50;
} reservoir_t;

#endif //FARMR_PINS_H
