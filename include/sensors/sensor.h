//
// Created by Josue Figueroa on 12/12/20.
//

#ifndef FARMR_SENSOR_H
#define FARMR_SENSOR_H

#include <Arduino.h>

class Sensor {
  public:
    enum SensName {
       None,
       Temperature,
       Humidity,
       Light,
       Ec,
       pH,
       Level,
       Nitrate,
       Nitrite,
       NH3
     };
    // Constructors
    explicit Sensor(const uint8_t &pin);
    Sensor(const Sensor&) = default;
    Sensor& operator=(const Sensor&) = default;

    // Destructor
    virtual ~Sensor();

    virtual SensName getType() const = 0;
    virtual void init() = 0;
    virtual void update() = 0;

  protected:
    uint8_t pin;
  };

#endif //FARMR_SENSOR_H
