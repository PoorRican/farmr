#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskScheduler.h>
#include "settings.h"

#ifdef SENSORLESS_OPERATION
#include "sensorless.h"
#endif

Scheduler ts;

Task readSerial(TASK_IMMEDIATE, TASK_FOREVER, &read_serial, &ts, true);

/**
 * Adds individual tasks for pumps and sensor operations to scheduler.
 */
void init_tasks() {
  // TOOD: convert this to a for-loop

  // Pump tasks
  acid_pump.addTasks(ts);
  base_pump.addTasks(ts);
  reservoir_pump.addTasks(ts);

  // Monitor Tasks
  ph_monitor.addTasks(ts);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // TODO: consolidate this to a dedicated function
  Serial.println("*******************");
  Serial.println("*      FARMR      *");
  Serial.println("*******************\n");

  // IO Initializations
  reservoir_pump.init();
  acid_pump.init();
  base_pump.init();

  // Build flags
  // TODO: Consolidate this to a dedicated function
  Serial.println("==============================================================");
  Serial.println("Features/Flags:");
#ifdef BASIC_TESTING
  Serial.println("BASIC_TESTING enabled...          All timing will be in seconds.");
#endif

#ifdef SENSORLESS_OPERATION
  Serial.println("SENSORLESS_OPERATION enabled...   Serial debugging is enabled.");
  Serial.println("==============================================================\n");
  init_sonar_levels();
  init_sCmd();
#endif

  // TaskScheduler Initialisations
  init_tasks();
}

void loop() {
  ts.execute();
}
