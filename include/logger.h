//
// Created by Josue Figueroa on 3/18/22.
//

#ifndef FARMR_LOGGER_H
#define FARMR_LOGGER_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <TimeLib.h>
#include "sensors/sensor.h"

/**
 * Defines logging levels and entry types.
 * Levels are inclusive of lower levels, So data is always logged.
 *
 * Levels:
 *  - Data: All sensor data
 *  - Error: Any system critical errors detected. Eg: catastrophic failures, anomalies
 *  - Warnings: Non-critical errors that may cause foreseeable problems in the future.
 *  - Debug: Critical function calls
 *  - Verbose: Indiscriminate function calls and logic exposure
 */
enum log_level {
  Data,
  Error,
  Warning,
  Debug,
  Verbose
};

struct event_t {
  time_t timestamp;
  log_level type;
  const char* data;
};

struct data_t {
  time_t timestamp;
  Sensor::SensName type;
  double data;
};

/// Filename for event data
static const char* EVENT_fn = "event.dat";

/// Filename for sensor data
static const char* DATA_fn = "data.dat";

#ifdef BASIC_TESTING
/**
 * Simulate a time if testing.
 */
static constexpr unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
void fake_time() {
  setTime(DEFAULT_TIME);
}
#endif

/**
 * Appends event log entry to file.
 */
inline void appendToFile(File* file, event_t entry);

/**
 * Appends data to file as binary.
 *
 * Binary is used to reduce overhead as per:::::::::::::::::::::::::::::::::
 */
inline void appendToFile(File* file, data_t entry);

class Logger {
public:

  enum class log_mode {
    // Report entries via serial
    Serial,

    // Store entries on filesystem
    File,

    // Both report and store entries
    All
  };

  explicit Logger(log_mode mode, log_level level=log_level::Warning);
  ~Logger();

  // High-level logging functions
  void data(Sensor::SensName type, double data);
  void warning(const char* s);
  void error(const char* s);
  void debug(const char* s);
  void verbose(const char* s);

protected:
  log_mode mode;
  log_level level;

  /// File that stores `event_t`
  File event_f;

  /// File that stores `data_t`
  File data_f;

  /**
   * Primary function used for writing event log entries.
   *
   * This function writes to serial and/or file based on `Logger::mode`
   */
  void log(event_t &entry);

  /**
   * Overridden function used for logging data.
   *
   * This function writes to serial and/or file based on `Logger::mode`
   */
  void log(data_t &entry);
};


#endif //FARMR_LOGGER_H
