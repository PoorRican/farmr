//
// Created by Josue Figueroa on 12/19/20.
//

#ifndef FARMR_SENSORLESS_H
#define FARMR_SENSORLESS_H


#ifdef SENSORLESS_OPERATION

#include <SerialCommand.h>
#include "settings.h"

extern SerialCommand sCmd;

/**
 * Wrapper to read serial accessible from the global scope
 */
void read_serial();

/**
 * Simply prints "heartbeat"
 */
void heartbeat();

void init_sCmd();

void unrecognized_command(const char*);

/**
 * Initializes preset levels of all mock sonar sensors
 * so that pumpPin-protection is not activated.
 */
void init_sensor_levels();

// reservoir operations
void start_reservoir_pumping();
void stop_reservoir_pumping();

void reservoir_above_threshold();
void reservoir_pump_on();

void set_reservoir_duration();
void get_reservoir_duration();

void set_reservoir_interval();
void get_reservoir_interval();

// pH operations
void set_ph();
void get_ph();

// pH Monitor operations
void start_ph_monitor_polling();
void stop_ph_monitor_polling();

void set_ph_monitor_polling_interval();
void get_ph_monitor_polling_interval();

void set_ph_monitor_ideal();
void get_ph_monitor_ideal();

void set_acid_pump_duration();
void get_acid_pump_duration();

void set_base_pump_duration();
void get_base_pump_duration();

#endif

#endif //FARMR_SENSORLESS_H
