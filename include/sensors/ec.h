//
// Created by Josue Figueroa on 12/13/20.
//

#ifndef FARMR_SENSOREC_H
#define FARMR_SENSOREC_H

#include "sensor.h"

class SensorEC: public Sensor {
public:
  explicit SensorEC(const uint8_t &pin);
  SensorEC(const SensorEC&) = default;
  SensorEC& operator=(const SensorEC&) = default;

  SensName getType() const override;

  void init() final;
  void update() final;
  double get() const;
  void calibrating(boolean c);

  // Circuit commands
  static void reset();
  static void getInfo();
  static void setLed(boolean);
  static void setContinuous();
  static void setStandby();
  static void setProbeType();
  static void setDry();
  static void setTenThousand();
  static void setFortyThousand();
  // Adjust EC sensor readings to given temp
  void adjustTemp(double) const;

protected:
  boolean isCalibrating = false;
  double ec;

  static void clearECBuffer() ;
  static void ecToSerial();
};


#endif //FARMR_SENSOREC_H
