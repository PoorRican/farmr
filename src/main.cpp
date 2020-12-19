#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskScheduler.h>
#include "settings.h"
#include "monitor_ph.h"
#include "pump_water.h"
#include "sensor_ping.h"
#include "SensorPH.h"

Scheduler ts;

// debug flag set in "sensor.h"
#ifdef SENSORLESS_OPERATION

#include <SerialCommand.h>

SerialCommand sCmd;

void init_sCmd();

void unrecognized_command(const char*);

/**
 * Initializes preset levels of all mock sonar sensors
 * so that pin-protection is not activated.
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

void set_base_pump_duration();
void get_base_pump_duration();

#endif

// PH Pumps/Sensor
pump_t acid_array = {25, 26, 27, 10};
Pump_pH acid_pump(acid_array.pin, acid_array.duration, &ts);

pump_t base_array = {28, 29, 30, 10};
Pump_pH base_pump(base_array.pin, base_array.duration, &ts);

// PH Monitor
SensorPH ph_sensor(ph_sensor_t.pin);
pHMonitor ph_monitor(ph_sensor_t.ideal, ph_sensor_t.interval, ph_sensor, acid_pump, base_pump, &ts);

// Reservoir
pump_t reservoir_array = {23, 24, 10, 10, 4};
SensorPing reservoir_sonar(23, 24);
WaterPump reservoir_pump(reservoir_array.pin, reservoir_array.interval, reservoir_array.interval, &reservoir_sonar, &ts);

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


#ifdef SENSORLESS_OPERATION
void init_sCmd() {
  sCmd.setDefaultHandler(unrecognized_command);

  // reservoir commands
  sCmd.addCommand("start reservoir pumping", start_reservoir_pumping);
  sCmd.addCommand("stop reservoir pumping", stop_reservoir_pumping);

  sCmd.addCommand("set reservoir pin duration", set_reservoir_pump_duration);
  sCmd.addCommand("get reservoir pin duration", get_reservoir_pump_duration);

  sCmd.addCommand("set reservoir pin interval", set_reservoir_pump_interval);
  sCmd.addCommand("get reservoir pin interval", get_reservoir_pump_interval);

  // pH sensor commands
  sCmd.addCommand("set ph", set_ph);
  sCmd.addCommand("get ph", get_ph);

  // pH monitor commands
  sCmd.addCommand("start ph monitor polling", start_ph_monitor_polling);
  sCmd.addCommand("stop ph monitor polling", stop_ph_monitor_polling);

  sCmd.addCommand("set ph monitor interval", set_ph_monitor_polling_interval);
  sCmd.addCommand("get ph monitor interval", get_ph_monitor_polling_interval);

  sCmd.addCommand("set ph ideal", set_ph_monitor_ideal);
  sCmd.addCommand("get ph ideal", get_ph_monitor_ideal);

  sCmd.addCommand("set acid_pump duration", set_acid_pump_duration);
  sCmd.addCommand("get acid_pump duration", get_acid_pump_duration);

  sCmd.addCommand("set base_pump duration", set_base_pump_duration);
  sCmd.addCommand("get base_pump duration", get_base_pump_duration);
}

void unrecognized_command(const char* command) {
  Serial.println("Unrecognized command...");
}

void init_sonar_levels() {
  reservoir_sonar.setMax(100);
  reservoir_sonar.setMin(0);
  reservoir_sonar.setLevel(50);
}

// Reservoir Operations
void start_reservoir_pumping() {
  reservoir_pump.startPumpOnTimer();
}
void stop_reservoir_pumping() {
  reservoir_pump.stopPumpOnTimer();
}

void set_reservoir_pump_duration() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    reservoir_pump.setDuration(atoi(arg));
    Serial.print("reservoir duration set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_reservoir_pump_duration() {
  Serial.print("reservoir duration is set to ");
  Serial.println(reservoir_pump.getDuration());
}

void set_reservoir_pump_interval() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    reservoir_pump.setInterval(atoi(arg));
    Serial.print("reservoir interval set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_reservoir_pump_interval() {
  Serial.print("reservoir interval is set to ");
  Serial.println(reservoir_pump.getInterval());
}

// pH Sensor Operations
void set_ph() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    ph_sensor.setPH(atof(arg));
    Serial.print("pH set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_ph() {
  Serial.print("pH is currently ");
  Serial.println(ph_sensor.get());
}

// pH Monitor Operations
void start_ph_monitor_polling() {
  ph_monitor.startPolling();
}
void stop_ph_monitor_polling() {
  ph_monitor.stopPolling();
}

void set_ph_monitor_polling_interval() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    uint16_t i = atoi(arg);
    ph_monitor.setInterval(i);
    Serial.print("pH polling interval set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_ph_monitor_polling_interval() {
  Serial.print("pH polling interval is currently ");
  Serial.println(ph_monitor.getInterval());
}

void set_ph_monitor_ideal() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    float i = atof(arg);
    ph_monitor.setIdeal(i);
    Serial.print("ideal pH set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_ph_monitor_ideal() {
  Serial.print("ideal pH is currently ");
  Serial.println(ph_monitor.getInterval());
}

void set_acid_pump_duration() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    float i = atof(arg);
    acid_pump.setDuration(i);
    Serial.print("acid_pump duration set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_acid_pump_duration() {
  Serial.print("acid_pump duration is currently ");
  Serial.println(acid_pump.getDuration());
}

void set_base_pump_duration() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    float i = atof(arg);
    base_pump.setDuration(i);
    Serial.print("base_pump duration set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_base_pump_duration() {
  Serial.print("base_pump duration is currently ");
  Serial.println(base_pump.getDuration());
}
#endif
