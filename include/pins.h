//
// Created by Josue Figueroa on 12/25/20.
//

#ifndef FARMR_PINS_H
#define FARMR_PINS_H

#include "Arduino.h"

#define ONE_WIRE_BUS 5

struct {
  const uint8_t acidPin = 52;
  const uint8_t basePin = 53;
  const uint8_t sensorPin = 2;
} ph_monitor_t;

struct {
  const uint8_t sensorPin = 3;
  const uint8_t pumpPin = 13;
} reservoir_t;

struct {
  const uint8_t sensorPin = ONE_WIRE_BUS;
  const uint8_t heaterPin = 50;
  const uint8_t coolerPin = 51;
  const uint8_t pumpPin = 49;
} temp_t;

#endif //FARMR_PINS_H
