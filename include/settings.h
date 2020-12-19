//
// Created by Josue Figueroa on 12/18/20.
//

#ifndef FARMR_SETTINGS_H
#define FARMR_SETTINGS_H

#include <Arduino.h>

struct pump_t {
  const uint8_t trigger;
  const uint8_t echo;
  const uint8_t pin;
  uint16_t duration;
  uint16_t interval;
};


struct {
  float ideal = 7.5;
  uint16_t interval = 10;
  uint8_t pin = 8;
} ph_sensor_t;

#endif //FARMR_SETTINGS_H