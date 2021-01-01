#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskScheduler.h>
#include "settings.h"
#include "scheduler.h"
#include "ui/UI_Main.h"
#include "buttons.h"
#include "startup.h"
#include "tasks.h"
#include "ui/UI_Feedback.h"

#ifdef SENSORLESS_OPERATION
#include "sensorless.h"
#endif

// Task Scheduler
Scheduler ts;
Task readSerialCmd(TASK_IMMEDIATE, TASK_FOREVER, &read_serial, &ts, true);
Task ui(TASK_IMMEDIATE, TASK_FOREVER, &pollUi, &ts, true);
Task updateSettings(100, TASK_FOREVER, &update_settings, &ts, true);
Task updateSensors(100, TASK_FOREVER, &update_sensors, &ts, true);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  lcd.begin(16,2);
  nav.showTitle = false;
  nav.timeOut = 15;
  nav.idleTask = idle;

  init_buttons();

  startup_msg();
  show_flags();

  init_memory();
  init_io();            // objects must be created before pumpPin initialization

  // Build flags
#ifdef SENSORLESS_OPERATION
  init_serial_operation();
#endif

  // TaskScheduler Initialisations
  init_tasks();

  start_services();
}

void loop() {
  ts.execute();
}
