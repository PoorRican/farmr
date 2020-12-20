#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskScheduler.h>
#include "settings.h"
#include "monitor_ph.h"
#include "pump_water.h"
#include "sensor_ping.h"
#include "SensorPH.h"
#ifdef SENSORLESS_OPERATION
#include "sensorless.h"
#endif

Scheduler ts;

/**
 * Adds individual tasks for pumps and sensor operations to scheduler.
 * TaskScheduler does not seem to recognize Task when it is a class-member of an object.
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

  // IO Initializations
  reservoir_pump.init();
  acid_pump.init();
  base_pump.init();

#ifdef SENSORLESS_OPERATION
  init_sonar_levels();
  init_sCmd();
#endif

  // TaskScheduler Initialisations
  ts.init();
  init_tasks();
}

void loop() {
#ifdef SENSORLESS_OPERATION
  sCmd.readSerial();
#endif
  ts.execute();
}
