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
  sCmd.addCommand("start.reservoir.pumping", start_reservoir_pumping);
  sCmd.addCommand("stop.reservoir.pumping", stop_reservoir_pumping);

  sCmd.addCommand("reservoir.above.threshold", reservoir_above_threshold);
  sCmd.addCommand("reservoir.pump.on", reservoir_pump_on);

  sCmd.addCommand("set.reservoir.pin.duration", set_reservoir_pump_duration);
  sCmd.addCommand("get.reservoir.pin.duration", get_reservoir_pump_duration);

  sCmd.addCommand("set.reservoir.pin.interval", set_reservoir_pump_interval);
  sCmd.addCommand("get.reservoir.pin.interval", get_reservoir_pump_interval);

  // pH sensor commands
  sCmd.addCommand("set.ph", set_ph);
  sCmd.addCommand("get.ph", get_ph);

  // pH monitor commands
  sCmd.addCommand("start.ph.monitor.polling", start_ph_monitor_polling);
  sCmd.addCommand("stop.ph.monitor.polling", stop_ph_monitor_polling);

  sCmd.addCommand("set.ph.monitor.interval", set_ph_monitor_polling_interval);
  sCmd.addCommand("get.ph.monitor.interval", get_ph_monitor_polling_interval);

  sCmd.addCommand("set.ph.ideal", set_ph_monitor_ideal);
  sCmd.addCommand("get.ph.ideal", get_ph_monitor_ideal);

  sCmd.addCommand("set.acid_pump.duration", set_acid_pump_duration);
  sCmd.addCommand("get.acid_pump.duration", get_acid_pump_duration);

  sCmd.addCommand("set.base_pump.duration", set_base_pump_duration);
  sCmd.addCommand("get.base_pump.duration", get_base_pump_duration);

  sCmd.addCommand("test", heartbeat);

  Serial.println("Serial commands initialized...");
}

void unrecognized_command(const char* command) {
  String s = "'" + (String)command + "' is an unrecognized command...";
  Serial.println(s);
}

void init_sonar_levels() {
  reservoir_sonar.setMax(100);
  reservoir_sonar.setMin(0);
  reservoir_sonar.setLevel(50);
  Serial.println("Sonar levels set...");
}

// Reservoir Operations
void start_reservoir_pumping() {
  Serial.println("Starting reservoir pumping");
  reservoir_pump.startPumpOnTimer();
}
void stop_reservoir_pumping() {
  Serial.println("Stopping reservoir pumping");
  reservoir_pump.stopPumpOnTimer();
}

void reservoir_above_threshold() {
  String s = "Reservoir is " + (String)(reservoir_pump.aboveThreshold() ? "above" : "below") + " threshold";
  Serial.println(s);
}

void reservoir_pump_on() {
  String s = "Reservoir pump is " + (String)(reservoir_pump.getPumpOn() ? "on" : "off");
  Serial.println(s);
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
