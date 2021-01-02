//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_SENSORPH_H
#define FARMR_SENSORPH_H

#include "sensor.h"

class SensorPH : public Sensor {
public:
  explicit SensorPH(const int &pin);
  SensorPH(const SensorPH&) = default;
  SensorPH& operator=(const SensorPH&) = default;
  ~SensorPH() override = default;

  SensName getType() const final;
  void init() final;
  void update() final;
  float get() const;

  // Avoids skewed readings
  void setCalibrating(boolean);

  // pH circuit commands
  static void reset();
  static void getInfo();
  static void setLed(boolean);
  static void setContinuous();
  static void setStandby();
  static void setFour();
  static void setSeven();
  static void setTen();

  // adjust pH readings
  void adjustTemp(float) const;

#ifdef SENSORLESS_OPERATION
  /**
   * Debug flag used for manually setting `pH`
   */
  void setPH(float val) {
    pH = val;
  }
#endif

protected:
  boolean isCalibrating = false;

  // post-smoothing value
  float pH;

  /**
   * Clear incoming buffer
   */
  static void clearBuffer();
  /**
   * Send raw sensor reading to `Serial`
   */
  static void phToSerial();
};


#endif //FARMR_SENSORPH_H
