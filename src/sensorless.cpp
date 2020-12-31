//
// Created by Josue Figueroa on 12/19/20.
//

#include "sensorless.h"

// defined in "platformio.ini" build_flags
#ifdef SENSORLESS_OPERATION

SerialCommand sCmd;

void read_serial() {
  sCmd.readSerial();
}

void heartbeat() {
  Serial.println("heartbeat");
}

void init_sCmd() {
  sCmd.setDefaultHandler(unrecognized_command);

  // reservoir commands
  sCmd.addCommand("start_reservoir_pumping", start_reservoir_pumping);
  sCmd.addCommand("stop_reservoir_pumping", stop_reservoir_pumping);

  sCmd.addCommand("reservoir_pump_on", reservoir_pump_on);
  sCmd.addCommand("reservoir_above_threshold", reservoir_above_threshold);

  sCmd.addCommand("set_reservoir_duration", set_reservoir_duration);
  sCmd.addCommand("get_reservoir_duration", get_reservoir_duration);

  sCmd.addCommand("set_reservoir_interval", set_reservoir_interval);
  sCmd.addCommand("get_reservoir_interval", get_reservoir_interval);

  // pH sensor commands
  sCmd.addCommand("set_ph", set_ph);
  sCmd.addCommand("get_ph", get_ph);

  // pH monitor commands
  sCmd.addCommand("start_ph_polling", start_ph_monitor_polling);
  sCmd.addCommand("stop_ph_polling", stop_ph_monitor_polling);

  sCmd.addCommand("set_ph_interval", set_ph_monitor_polling_interval);
  sCmd.addCommand("get_ph_interval", get_ph_monitor_polling_interval);

  sCmd.addCommand("set_ph.ideal", set_ph_monitor_ideal);
  sCmd.addCommand("get_ph.ideal", get_ph_monitor_ideal);

  sCmd.addCommand("set_acid_pump_duration", set_acid_pump_duration);
  sCmd.addCommand("get_acid_pump_duration", get_acid_pump_duration);

  sCmd.addCommand("set_base_pump_duration", set_base_pump_duration);
  sCmd.addCommand("get_base_pump_duration", get_base_pump_duration);

  sCmd.addCommand("test", heartbeat);

#ifdef VERBOSE_OUTPUT
  Serial.println("Serial commands initialized...\n");
#endif
}

void unrecognized_command(const char* command) {
  String s = "'" + (String)command + "' is an unrecognized command...";
  Serial.println(s);
}

void init_sensor_levels() {
  Serial.println("Simulating sensor levels...");

  // Reservoir Sonar
  reservoir_level->setLevel(50);

  // pH Sensor
  ph_sensor->setPH(7.0);
}

// Reservoir Operations
void start_reservoir_pumping() {
  Serial.println("Starting reservoir pumping");
  reservoir_pump->startPumpOnTimer();
}
void stop_reservoir_pumping() {
  Serial.println("Stopping reservoir pumping");
  reservoir_pump->stopPumpOnTimer();
  reservoir_pump->stopPumpOffTimer();
}

void reservoir_above_threshold() {
  String s = "Reservoir is " + (String)(reservoir_pump->aboveThreshold() ? "above" : "below") + " threshold";
  Serial.println(s);
}

void reservoir_pump_on() {
  String s = "Reservoir pump is " + (String)(reservoir_pump->getPumpOn() ? "on" : "off");
  Serial.println(s);
}

void set_reservoir_duration() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    reservoir->setDuration(atoi(arg));
    Serial.print("reservoir duration set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_reservoir_duration() {
  Serial.print("reservoir duration is set to ");
  Serial.println(reservoir->getDuration());
}

void set_reservoir_interval() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    reservoir->setInterval(atoi(arg));
    Serial.print("reservoir interval set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_reservoir_interval() {
  Serial.print("reservoir interval is set to ");
  Serial.println(reservoir->getInterval());
}

// pH Sensor Operations
void set_ph() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    ph_sensor->setPH(atof(arg));
    Serial.print("pH set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_ph() {
  Serial.print("pH is currently ");
  Serial.println(ph_sensor->get());
}

// pH Monitor Operations
void start_ph_monitor_polling() {
  ph_monitor->startPolling();
}
void stop_ph_monitor_polling() {
  ph_monitor->stopPolling();
}

void set_ph_monitor_polling_interval() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    uint16_t i = atoi(arg);
    ph_monitor->setInterval(i);
    Serial.print("pH polling interval set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_ph_monitor_polling_interval() {
  Serial.print("pH polling interval is currently ");
  Serial.println(ph_monitor->getInterval());
}

void set_ph_monitor_ideal() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    float i = atof(arg);
    ph_monitor->setIdeal(i);
    Serial.print("ideal pH set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_ph_monitor_ideal() {
  Serial.print("ideal pH is currently ");
  Serial.println(ph_monitor->getIdeal());
}

void set_acid_pump_duration() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    float i = atof(arg);
    acid_pump->setDuration(i);
    Serial.print("acid_pump duration set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_acid_pump_duration() {
  Serial.print("acid_pump duration is currently ");
  Serial.println(acid_pump->getDuration());
}

void set_base_pump_duration() {
  char* arg;
  arg = sCmd.next();
  if (arg != nullptr) {
    float i = atof(arg);
    base_pump->setDuration(i);
    Serial.print("base_pump duration set to ");
    Serial.println(arg);
  }
  else {
    Serial.println("no argument given");
  }
}
void get_base_pump_duration() {
  Serial.print("base_pump duration is currently ");
  Serial.println(base_pump->getDuration());
}
#endif
