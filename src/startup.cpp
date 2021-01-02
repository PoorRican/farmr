//
// Created by Josue Figueroa on 12/28/20.
//

#include "../include/startup.h"

void startup_msg() {
  Serial.println("*******************");
  Serial.println("*      FARMR      *");
  Serial.println("*******************\n");

  lcd.setCursor(0, 1);
  lcd.print("****************");
  delay(300);

  lcd.setCursor(0, 0);
  lcd.print("****************");
  lcd.setCursor(0, 1);
  lcd.print("<*    FARMR   *>");
  delay(750);

  lcd.setCursor(0, 0);
  lcd.print("<*    FARMR   *>");
  lcd.setCursor(0, 1);
  lcd.print("****************");
  delay(750);

  lcd.setCursor(0, 0);
  lcd.print("****************");
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  delay(300);
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

void updatePrompt() {
  if (settings.checkVersion()) {

#ifdef VERBOSE_OUTPUT
    Serial.println("New Version Detected!!\n");
#endif

    lcd.setCursor(0, 0);
    lcd.print("* New Version  *");
    lcd.setCursor(0, 1);
    lcd.print("* Detected     *");
    delay(1000);

    lcd.setCursor(0, 0);
    lcd.print("Press Sel to    ");
    lcd.setCursor(0, 1);
    lcd.print("Reset Settings  ");

    unsigned long timer = millis();
    while ((millis() - timer) < 5000 && !updateEEPROM) {
      analogButtons.check();
    }
    if (updateEEPROM) {
      settings.writeDefaults();

      lcd.setCursor(0, 0);
      lcd.print("Default Settings");
      lcd.setCursor(0, 1);
      lcd.print("Restored...     ");
      delay(1000);
    }
  }
#ifdef VERBOSE_OUTPUT
  else {
    Serial.println("No new version detected\n");
  }
#endif
}

void init_io() {
  reservoir_pump->init();

  acid_pump->init();
  base_pump->init();

  sensor_temp->init();
  heating_element->init();
  cooling_element->init();
  pump_temp->init();
}

void init_serial_operation() {
  init_sensor_levels();
  init_sCmd();
}

void init_memory() {
  updatePrompt();

  settings.readValues();
  Settings::init_objects();
}

void start_services() {
  if (pumpingOn) {
    reservoir_pump->startRelayOnTimer();
  }
  if (phMonitoring) {
    ph_monitor->startPolling();
  }

  if (tempMonitoring) {
    monitor_temp->startPolling();
  }
}