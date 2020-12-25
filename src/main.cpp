#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskScheduler.h>
#include "settings.h"
#include "scheduler.h"

#ifdef SENSORLESS_OPERATION
#include "sensorless.h"
#endif

Scheduler ts;

Task readSerial(TASK_IMMEDIATE, TASK_FOREVER, &read_serial, &ts, true);

void startup_msg() {
  Serial.println("*******************");
  Serial.println("*      FARMR      *");
  Serial.println("*******************\n");
}

void show_flags() {
  Serial.println("==============================================================");
  Serial.println("Features/Flags:");

#ifdef BASIC_TESTING
  Serial.println("BASIC_TESTING enabled...          All timing will be in seconds.");
#endif

#ifdef SENSORLESS_OPERATION
  Serial.println("SENSORLESS_OPERATION enabled...   Serial debugging is enabled.");
#endif

  Serial.println("==============================================================\n");
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Serial Startup
  startup_msg();
  show_flags();

  // IO Initializations
  reservoir_pump.init();
  acid_pump.init();
  base_pump.init();

  // Build flags

#ifdef SENSORLESS_OPERATION
  init_sonar_levels();
  init_sCmd();
#endif

  // TaskScheduler Initialisations
  init_tasks();
}

void loop() {
  ts.execute();
}
