//
// Created by Josue Figueroa on 12/18/20.
//

#ifndef FARMR_SETTINGS_H
#define FARMR_SETTINGS_H

#define VERSION 0.1

// pH Monitor Defualts
#define IDEAL_PH 7.5
#define PH_MONITOR_ENABLED true
#define PH_POLL_INTERVAL 15
#define PH_POLL_DURATION 2

// Reservoir Defaults
#define RESERVOIR_PUMPING_ENABLED true
#define RESERVOIR_THRESHOLD 25
#define RESERVOIR_DURATION 5
#define RESERVOIR_INTERVAL 4
#define RESERVOIR_CALIBRATION_MAX 110
#define RESERVOIR_CALIBRATION_MIN 10

#include <Arduino.h>
#include "pump_water.h"
#include "sensor_ping.h"
#include "pump_ph.h"
#include "monitor_ph.h"
#include <EEPROMex.h>

// pH Monitor Variables
extern bool phMonitoring;
extern float idealPh;
extern uint16_t phPollInterval;
extern uint16_t phPumpDuration;

// Reservoir Variables
extern bool pumpingOn;
extern uint16_t threshold;
extern uint16_t reservoirDuration;
extern uint16_t reservoirInterval;
extern uint16_t reservoirMax;
extern uint16_t reservoirMin;


template <typename T>
struct mem_t {
  int address;
  T* value;
};

class Settings {
public:
  Settings();
  /**
   * Initializes all addresses.
   */
  void getAddresses();
  /**
   * Reads values from EEPROM to RAM
   */
  void readValues();
  /**
   * Writes values from RAM to EEPROM
   */
  void updateValues() const;
  /**
   * Initializes global objects
   */
  void init_objects() const;

  /**
   * Writes default values to EEPROM.
   */
  void writeDefaults() const;

  /**
   * Compares version in EEPROM against local variable.
   * @return
   */
  bool checkVersion() const;

private:
  mem_t<float> version;

  mem_t<bool> ph_mon_enabled;
  mem_t<float> ideal_ph;
  mem_t<uint16_t> ph_pump_duration;
  mem_t<uint16_t> ph_polling_interval;

  mem_t<bool> reservoir_pump_enabled;
  mem_t<uint16_t> reservoir_pump_duration;
  mem_t<uint16_t> reservoir_pump_interval;
  mem_t<uint16_t> reservoir_calibration_max;
  mem_t<uint16_t> reservoir_calibration_min;
  mem_t<uint16_t> reservoir_threshold;
};

extern Settings settings;

// pH Pumps/Sensors/Monitor
extern Pump_pH *acid_pump;
extern Pump_pH *base_pump;

extern SensorPH *ph_sensor;
extern pHMonitor *ph_monitor;

// Reservoir
extern SensorPing *reservoir_sonar;
extern WaterPump *reservoir_pump;

#endif //FARMR_SETTINGS_H