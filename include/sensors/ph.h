//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_SENSORPH_H
#define FARMR_SENSORPH_H

#include "sensor.h"

/**
 * Interface for pH sensor.
 *
 * Communicates over `Serial2`.
 */
class SensorPH : public Sensor {
  public:
    explicit SensorPH(const uint8_t &pin);
    SensorPH(const SensorPH&) = default;
    SensorPH& operator=(const SensorPH&) = default;
    ~SensorPH() override = default;

    SensName getType() const final;
    void init() final;
    void update() final;
    double get() const;

    // Avoids skewed readings
    void setCalibrating(bool);

    // pH circuit commands
    static void reset();
    static void getInfo();
    static void setLed(bool);
    static void setContinuous();
    static void setStandby();
    static void setFour();
    static void setSeven();
    static void setTen();

    // adjust pH readings
    void adjustTemp(double) const;

  #ifdef SENSORLESS_OPERATION
    /**
    * Debug flag used for manually setting `pH`
    */
    void setPH(double val) {
      pH = val;
    }
  #endif

  protected:
    bool isCalibrating = false;

    double pH;

    /**
    * Clear incoming buffer
    */
    static void clearBuffer();

    /**
     * DEPRECATED
     * Send raw sensor reading to `Serial`
     */
    static void phToSerial();
  };


#endif //FARMR_SENSORPH_H
