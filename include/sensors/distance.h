//
// Created by Josue Figueroa on 12/29/20.
//

#ifndef FARMR_SENSORDISTANCE_H
#define FARMR_SENSORDISTANCE_H

#include "sensor.h"

#define LEVEL_SERIES_RESISTOR 560

class SensorDistance : public Sensor {
public:
  explicit SensorDistance(const uint8_t &pin);
  SensorDistance(const SensorDistance&) = default;
  SensorDistance& operator=(const SensorDistance&) = default;


  ~SensorDistance() override = default;

  SensName getType() const final;

  void init() final;
  uint8_t get() const;
  void update() final;

  /**
   * Calibrates level minimum to current sensor reading
   */
  void calibrateMin();
  /**
   * Calibrates level maximum to current sensor reading
   */
  void calibrateMax();

  bool aboveThreshold() const;
  uint8_t getThreshold() const;
  bool setThreshold(const uint8_t&);

#ifdef SENSORLESS_OPERATION
  /**
   * Debug function used for simulating water level
   */
   void setLevel(uint8_t val) {
     level = val;
   }
#endif

protected:
  float max = 0;
  float min = 0;
  uint8_t threshold = 25;
  uint8_t level = 0;

  /**
   * Returns resistance of analog pumpPin in Ohms
   * Taken from https://www.adafruit.com/products/1786
   */
  float readResistance() const;
};

#endif //FARMR_DISTANCE_H
