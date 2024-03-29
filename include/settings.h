//
// Created by Josue Figueroa on 12/18/20.
//

#ifndef FARMR_SETTINGS_H
#define FARMR_SETTINGS_H

#define VERSION 0.21

// pH Monitor Defaults
#define IDEAL_PH 7.5
#define PH_MONITOR_ENABLED false
#define PH_POLL_INTERVAL 15
#define PH_POLL_DURATION 2

// Reservoir Defaults
#define RESERVOIR_PUMP_MODE 0   // this should default to `PumpMode::Off`
#define RESERVOIR_THRESHOLD 25
#define RESERVOIR_DURATION 5
#define RESERVOIR_INTERVAL 4
#define RESERVOIR_CALIBRATION_MAX 110
#define RESERVOIR_CALIBRATION_MIN 10

// Temperature Defaults
#define IDEAL_TEMP 23.89
#define TEMP_MONITORING_ENABLED false
#define TEMP_DURATION 15
#define TEMP_INTERVAL 30

#include <Arduino.h>
#include <EEPROMex.h>
#include "monitor/temp.h"
#include "monitor/ph.h"
#include "reservoir.h"

// pH Pumps/Sensors/Monitor
extern ReagentPump *acid_pump;
extern ReagentPump *base_pump;

extern SensorPH *ph_sensor;
extern MonitorPh *ph_monitor;

// Reservoir
extern SensorDistance *reservoir_level;
extern WaterPump *reservoir_pump;
extern Reservoir *reservoir;

// Temperature
extern OneWire oneWire;
extern DallasTemperature *temperatureSensor;
extern SensorTemp *sensor_temp;
extern ThermoElectricElement *heating_element;
extern ThermoElectricElement *cooling_element;
extern WaterPump *pump_temp;
extern MonitorTemp *monitor_temp;

// Global Variables
extern bool updateEEPROM;
extern double swVersion;

// pH Monitor Variables
extern bool phMonitoring;
extern double idealPh;
extern uint16_t phPollInterval;
extern uint16_t phPumpDuration;

// Reservoir Variables
extern Reservoir::PumpMode pumpMode;
extern uint16_t threshold;
extern uint16_t reservoirDuration;
extern uint16_t reservoirInterval;
extern uint16_t reservoirMax;
extern uint16_t reservoirMin;

// Temperature Variables
extern bool tempMonitoring;
extern double idealTemp;
extern uint16_t tempInterval;
extern uint16_t tempDuration;

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
  static void init_objects();

  /**
   * Writes default values to EEPROM.
   */
  void writeDefaults() const;

  /**
   * Compares version in EEPROM against local variable.
   * @return
   */
  bool checkVersion() const;
  void updateVersion() const;

private:
  mem_t<double> version;

  mem_t<bool> ph_mon_enabled;
  mem_t<double> ideal_ph;
  mem_t<uint16_t> ph_pump_duration;
  mem_t<uint16_t> ph_polling_interval;

  mem_t<Reservoir::PumpMode> reservoir_pump_mode;
  mem_t<uint16_t> reservoir_pump_duration;
  mem_t<uint16_t> reservoir_pump_interval;
  mem_t<uint16_t> reservoir_calibration_max;
  mem_t<uint16_t> reservoir_calibration_min;
  mem_t<uint16_t> reservoir_threshold;

  mem_t<bool> temp_mon_enabled;
  mem_t<double> ideal_temp;
  mem_t<uint16_t> temp_duration;
  mem_t<uint16_t> temp_interval;
};

extern Settings settings;

void update_settings();

#endif //FARMR_SETTINGS_H