//
// Created by Josue Figueroa on 12/18/20.
//

#ifndef FARMR_SENSORLESS_OPERATION_H
#define FARMR_SENSORLESS_OPERATION_H

#include <SerialCommand.h>
#include "settings.h"

SerialCommand sCmd;

void init_sCmd();

void unrecognized_command(const char*);

/**
 * Initializes preset levels of all mock sonar sensors
 * so that pump-protection is not activated.
 */
void init_sonar_levels();

// reservoir operations
void start_reservoir_pumping();
void stop_reservoir_pumping();

void set_reservoir_pump_duration();
void get_reservoir_pump_duration();

void set_reservoir_pump_interval();
void get_reservoir_pump_interval();

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

void set_acid_pump_interval();
void get_acid_pump_interval();

void set_base_pump_duration();
void get_base_pump_duration();

void set_base_pump_interval();
void get_base_pump_interval();

#endif //FARMR_SENSORLESS_OPERATION_H