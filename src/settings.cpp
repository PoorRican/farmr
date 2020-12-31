//
// Created by Josue Figueroa on 12/19/20.
//

#include "settings.h"
#include "pins.h"

extern Scheduler ts;

Settings settings;

Pump_pH *acid_pump = nullptr;
Pump_pH *base_pump = nullptr;
SensorPH *ph_sensor = nullptr;
pHMonitor *ph_monitor = nullptr;

SensorLevel *reservoir_level = nullptr;
WaterPump *reservoir_pump = nullptr;

double swVersion = VERSION;
bool updateEEPROM = false;

// pH Monitor Variables
bool phMonitoring = PH_MONITOR_ENABLED;
float idealPh = IDEAL_PH;
uint16_t phPumpDuration = PH_POLL_DURATION;
uint16_t phPollInterval = PH_POLL_INTERVAL;

// Reservoir Variables
bool pumpingOn = RESERVOIR_PUMPING_ENABLED;
uint16_t threshold = RESERVOIR_THRESHOLD;
uint16_t reservoirDuration = RESERVOIR_DURATION;
uint16_t reservoirInterval = RESERVOIR_INTERVAL;
uint16_t reservoirMax = RESERVOIR_CALIBRATION_MAX;
uint16_t reservoirMin = RESERVOIR_CALIBRATION_MIN;

Settings::Settings() {
  getAddresses();

  version.value = &swVersion;

  // Init pH Monitor pointers
  ph_mon_enabled.value = &phMonitoring;
  ideal_ph.value = &idealPh;
  ph_pump_duration.value = &phPumpDuration;
  ph_polling_interval.value = &phPollInterval;

  // Init Reservoir pointers
  reservoir_pump_enabled.value = &pumpingOn;
  reservoir_pump_duration.value = &reservoirDuration;
  reservoir_pump_interval.value = &reservoirInterval;
  reservoir_calibration_max.value = &reservoirMax;
  reservoir_calibration_min.value = &reservoirMin;
  reservoir_threshold.value = &threshold;
}

void Settings::getAddresses() {
  // NOTE: this order MUST remain constant

  version.address = EEPROM.getAddress(sizeof(float));

  // pH Pump/Monitor
  ph_mon_enabled.address = EEPROM.getAddress(sizeof(int));
  ideal_ph.address = EEPROM.getAddress(sizeof(float));
  ph_pump_duration.address = EEPROM.getAddress(sizeof(unsigned int));
  ph_polling_interval.address = EEPROM.getAddress(sizeof(unsigned int));

  // Reservoir
  reservoir_pump_enabled.address = EEPROM.getAddress(sizeof(int));
  reservoir_pump_duration.address = EEPROM.getAddress(sizeof(unsigned int));
  reservoir_pump_interval.address = EEPROM.getAddress(sizeof(unsigned int));
  reservoir_calibration_max.address = EEPROM.getAddress(sizeof(unsigned int));
  reservoir_calibration_min.address = EEPROM.getAddress(sizeof(unsigned int));
  reservoir_threshold.address = EEPROM.getAddress(sizeof(unsigned int));
}

void Settings::readValues() {
  // pH Pump/Monitor
  *(ph_mon_enabled.value) = (bool)EEPROM.readInt(ph_mon_enabled.address);
  *(ideal_ph.value) = EEPROM.readFloat(ideal_ph.address);
  *(ph_pump_duration.value) = EEPROM.readInt(ph_pump_duration.address);
  *(ph_polling_interval.value) = EEPROM.readInt(ph_polling_interval.address);

  // Reservoir
  *(reservoir_pump_enabled.value) = (bool)EEPROM.readInt(reservoir_pump_enabled.address);
  *(reservoir_pump_duration.value) = EEPROM.readInt(reservoir_pump_duration.address);
  *(reservoir_pump_interval.value) = EEPROM.readInt(reservoir_pump_interval.address);
  *(reservoir_calibration_max.value) = EEPROM.readInt(reservoir_calibration_max.address);
  *(reservoir_calibration_min.value) = EEPROM.readInt(reservoir_calibration_min.address);
  *(reservoir_threshold.value) = EEPROM.readInt(reservoir_threshold.address);
}

void Settings::updateValues() const {
  EEPROM.updateInt(ph_mon_enabled.address, (int)phMonitoring);
  EEPROM.updateFloat(ideal_ph.address, idealPh);
  EEPROM.updateInt(ph_pump_duration.address, phPumpDuration);
  EEPROM.updateInt(ph_polling_interval.address, phPollInterval);

  EEPROM.updateInt(reservoir_pump_enabled.address, (int)pumpingOn);
  EEPROM.updateInt(reservoir_threshold.address, threshold);
  EEPROM.updateInt(reservoir_pump_duration.address, reservoirDuration);
  EEPROM.updateInt(reservoir_pump_interval.address, reservoirInterval);
  EEPROM.updateInt(reservoir_calibration_max.address, reservoirMax);
  EEPROM.updateInt(reservoir_calibration_min.address, reservoirMin);
}

void Settings::init_objects() {
  // Init pH Monitor Objects
  acid_pump = new Pump_pH(ph_monitor_t.acidPin, phPumpDuration, &ts);
  base_pump = new Pump_pH(ph_monitor_t.basePin, phPumpDuration, &ts);
  ph_sensor = new SensorPH(ph_monitor_t.sensorPin);
  ph_monitor = new pHMonitor(idealPh, phPollInterval, *ph_sensor, *acid_pump, *base_pump, &ts);

  // Init Reservoir Objects
  reservoir_level = new SensorLevel(reservoir_t.sensorPin);
  reservoir_pump = new WaterPump(reservoir_t.pumpPin, reservoirDuration, reservoirInterval, reservoir_level, &ts);
}

void Settings::writeDefaults() const {
#ifdef BASIC_TESTING
  Serial.println("Restoring default values...");
#endif
  updateVersion();

  // pH Pump/Monitor
  EEPROM.updateInt(ph_mon_enabled.address, (int)PH_MONITOR_ENABLED);
  EEPROM.updateFloat(ideal_ph.address, IDEAL_PH);
  EEPROM.updateInt(ph_pump_duration.address, PH_POLL_DURATION);
  EEPROM.updateInt(ph_polling_interval.address, PH_POLL_DURATION);

  // Reservoir
  EEPROM.updateInt(reservoir_pump_enabled.address, (int)RESERVOIR_PUMPING_ENABLED);
  EEPROM.updateInt(reservoir_pump_duration.address, RESERVOIR_DURATION);
  EEPROM.updateInt(reservoir_pump_interval.address, RESERVOIR_INTERVAL);
  EEPROM.updateInt(reservoir_calibration_max.address, RESERVOIR_CALIBRATION_MAX);
  EEPROM.updateInt(reservoir_calibration_min.address, RESERVOIR_CALIBRATION_MIN);
  EEPROM.updateInt(reservoir_threshold.address, RESERVOIR_THRESHOLD);

  init_objects();
}

bool Settings::checkVersion() const {
  double storedVersion = EEPROM.readDouble(version.address);
#ifdef BASIC_TESTING
  Serial.print("SW Version: ");
  Serial.println(swVersion);
  Serial.print("EEPROM Version: ");
  Serial.println(storedVersion);
#endif
  return swVersion != storedVersion;
}

void Settings::updateVersion() const {
#ifdef VERBOSE_OUTPUT
  Serial.println("Updated version value on EEPROM");
#endif
  EEPROM.writeDouble(version.address, swVersion);
}

void update_settings() {
  settings.updateValues();
}