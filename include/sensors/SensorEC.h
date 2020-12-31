//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_SENSOREC_H
#define FARMR_SENSOREC_H

#include "sensor.h"

class SensorEC: public Sensor {
public:
  explicit SensorEC(const int &pin);
  SensorEC(const SensorEC&) = default;
  SensorEC& operator=(const SensorEC&) = default;

  SensName getType() const;

  void init();
  void update();
  void fastUpdate();
  uint16_t get() const;
  uint16_t getRaw() const;      // returns EC in uSiemens. Should take 1000ms
  void calibrating(boolean c);

  // Circuit commands
  void reset();
  void getInfo();
  void setLed(boolean);
  void setContinuous();
  void setStandby();
  void setProbeType();
  void setDry();
  void setTenThousand();
  void setFortyThousand();
  // Adjust EC sensor readings to given temp
  void adjustTemp(float);

protected:
  boolean isCalibrating = false;
  uint8_t sample_counter = 0;
  uint16_t readings[sample_size];
  uint16_t ec;

  void smooth();
  void clearECBuffer() const;
  void ecToSerial();
};


#endif //FARMR_SENSOREC_H
