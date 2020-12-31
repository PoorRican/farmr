//
// Created by Josue Figueroa on 12/25/20.
//

#ifndef FARMR_PINS_H
#define FARMR_PINS_H

#include "Arduino.h"

#define ONE_WIRE_BUS 1

struct {
  const uint8_t acidPin = 52;
  const uint8_t basePin = 53;
  const uint8_t sensorPin = 2;
} ph_monitor_t;

struct {
  const uint8_t sensorPin = 0;
  const uint8_t pumpPin = 13;
} reservoir_t;

struct {
  const uint8_t sensorPin = ONE_WIRE_BUS;
  const uint8_t heaterPin = 54;
  const uint8_t coolerPin = 55;
} temp_t;

#endif //FARMR_PINS_H
