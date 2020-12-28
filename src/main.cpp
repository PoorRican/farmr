#define _TASK_LTS_POINTER       // Compile with support for local task storage pointer

#include <Arduino.h>
#include <TaskScheduler.h>
#include "settings.h"
#include "scheduler.h"
#include "UI_Main.h"
#include "buttons.h"

#ifdef SENSORLESS_OPERATION
#include "sensorless.h"
#endif

// Task Scheduler
Scheduler ts;
Task readSerialCmd(TASK_IMMEDIATE, TASK_FOREVER, &read_serial, &ts, true);
Task ui(TASK_IMMEDIATE, TASK_FOREVER, &pollUi, &ts, true);
Task updateSettings(100, TASK_FOREVER, &update_settings, &ts, true);

void startup_msg() {
  Serial.println("*******************");
  Serial.println("*      FARMR      *");
  Serial.println("*******************\n");
}
void lcd_startup_msg() {
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

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // LCD
  lcd.begin(16,2);
  lcd_startup_msg();
  //nav.showTitle = false;

  init_buttons();

  show_flags();
  startup_msg();

  updatePrompt();

  settings.readValues();
  Settings::init_objects();

  // IO Initializations
  reservoir_pump->init();
  acid_pump->init();
  base_pump->init();

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
