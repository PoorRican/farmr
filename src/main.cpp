#include <Arduino.h>
#include "settings.h"
#include "monitor_ph.h"
#include "pump_water.h"
#include "sensor_ping.h"
#include "SensorPH.h"
#include "scheduler.h"

// debug flag set in ~sensor.h"
#ifdef SENSORLESS_OPERATION
#include "sensorless_operation.h"
#endif


void setup() {
  Serial.begin(9600);
  while (!Serial);
  reservoir_pump.init();
  acid_pump.init();
  base_pump.init();

#ifdef SENSORLESS_OPERATION
  init_sonar_levels();
  init_sCmd();
#endif

  reservoir_pump.startPumpOnTimer();
  ph_monitor.startPolling();
}

void loop() {
  sCmd.readSerial();
  ts.execute();
}
