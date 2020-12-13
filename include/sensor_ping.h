//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_SENSOR_PING_H
#define FARMR_SENSOR_PING_H


#include "sensor.h"
#include <NewPing.h>

class SensorPing: public Sensor {
public:
  SensorPing(int, int);
  SensorPing(const SensorPing&);
  SensorPing& operator=(const SensorPing&);
  ~SensorPing();

  SensName getType() const;

  void init();
  void update();
  void fastUpdate();

  uint8_t get() const;
  uint16_t getRaw();
  uint8_t getPercent();

  // Calibration functions
  void setMax(uint16_t = 0);
  void setMin(uint16_t = 0);
  /**
   * Debug function used for simulating water level
   */
  void setLevel(uint8_t);

protected:
  int pinTrigger;
  int pinEcho;

  NewPing sonar;

  uint16_t max;
  uint16_t min;

  // Smoothing counter
  uint8_t samples;

  uint8_t levels[sample_size];
  uint8_t level;

  void smooth();
};


#endif //FARMR_SENSOR_PING_H
