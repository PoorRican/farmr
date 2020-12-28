//
// Created by Josue Figueroa on 12/28/20.
//

#ifndef FARMR_STARTUP_H
#define FARMR_STARTUP_H

#include <LiquidCrystal.h>
#include <Arduino.h>
#include "sensorless.h"
#include "buttons.h"
#include "settings.h"

extern LiquidCrystal lcd;

/**
 * Splash screen on LCD and header in Serial
 */
void startup_msg();

/**
 * Shows what build flags are enabled
 */
void show_flags();

/**
 * Asks to restore default settings if new version detected
 */
void updatePrompt();

/**
 * Initializes all IO pins.
 * `init_memory` must be called before this.
 */
void init_io();

void init_serial_operation();

/**
 * Initializes both EEPROM and RAM
 */
void init_memory();

#endif //FARMR_STARTUP_H
