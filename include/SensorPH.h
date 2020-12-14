//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_SENSORPH_H
#define FARMR_SENSORPH_H

#include <SoftwareSerial.h>
#include "sensor.h"

class SensorPH : public Sensor {
public:
  explicit SensorPH(const int &pin, SoftwareSerial*);
  SensorPH(const SensorPH&) = default;
  SensorPH& operator=(const SensorPH&) = default;
  ~SensorPH() override = default;

  SensName getType() const;
  void init() final;
  void update() final;
  void fastUpdate() final;
  float get() const;
  float getRaw() const;

  // Avoids skewed readings
  void setCalibrating(boolean);

  // pH circuit commands
  void reset();
  void getInfo();
  void setLed(boolean);
  void setContinuous();
  void setStandby();
  void setFour();
  void setSeven();
  void setTen();

  // adjust pH readings
  void adjustTemp(float);

protected:
  SoftwareSerial *serial = nullptr;
  boolean isCalibrating = false;
  uint8_t sample_counter = 0;

  float readings[sample_size];
  // post-smoothing value
  float pH;

  void smooth() final;
  /**
   * Clear incoming buffer
   */
  void clearBuffer();
  /**
   * Send raw sensor reading to `Serial`
   */
  void phToSerial();
};


#endif //FARMR_SENSORPH_H
