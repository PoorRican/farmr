//
// Created by Josue Figueroa on 12/13/20.
//

#include "SensorPH.h"

SensorPH::SensorPH(const int &pin) : Sensor(pin) {
  for (uint8_t i = 0; i < sample_size; i++) {
    readings[i] = 0;
  }
}

Sensor::SensName SensorPH::getType() const {
  return Sensor::pH;
}

void SensorPH::init() {
  // Begin communication
  Serial2.begin(38400);
  // reading on-demand mode
  Serial2.print("E\r");
  // make a reading to allow `fastUpdate` to work
  Serial2.print("R\r");
}

void SensorPH::update() {
#ifndef SENSORLESS_OPERATION
  readings[sample_counter++] = getRaw();
  sample_counter = sample_counter % sample_size;
  smooth();
#endif
}

void SensorPH::fastUpdate() {
  float p = getRaw();
  for (uint8_t i = 0; i < sample_size; i++) {
    readings[i] = p;
  }
  smooth();
}

float SensorPH::get() const {
  return pH;
}

float SensorPH::getRaw() const {
  if (!isCalibrating) {
    Serial2.print("R\r");
    if (Serial2.available() > 0) {
      float res = Serial2.parseFloat();
      Serial2.read();
      return res;
    }
    return 0;     // there is an error
  }
  else {
    return pH;    // last known pH
  }
}

void SensorPH::setCalibrating(boolean c) {
  isCalibrating = c;
}

void SensorPH::reset() {
  clearBuffer();
  Serial2.print("I\r");
  delay(10);
  phToSerial();
}

void SensorPH::getInfo() {
  clearBuffer();
  Serial2.print("I\r");
  delay(10);
  phToSerial();
}

void SensorPH::setLed(boolean state) {
  (state) ? Serial2.print("L1\r") : Serial2.print("L0\r");
}

void SensorPH::setContinuous() {
  Serial2.print("C\r");
}

void SensorPH::setStandby() {
  Serial2.print("E\r");
}

void SensorPH::setFour() {
  Serial2.print("F\r");
}

void SensorPH::setSeven() {
  Serial2.print("T\r");
}

void SensorPH::setTen() {
  Serial2.print("T\r");
}

void SensorPH::adjustTemp(float temp) {
  if (temp != 0 && !isCalibrating) {
    char tempArray[4];
    dtostrf(temp, 4, 2, tempArray);
    String command = (String)tempArray + "\r";
    Serial2.print(command);
  }
}

void SensorPH::smooth() {
  float res = 0;
  for (uint8_t i = 0; i < sample_counter; i++) {
    res += readings[i];
  }
  pH = (float)(res / sample_counter);
}

void SensorPH::clearBuffer() {
  while (Serial2.available() > 0) {
    Serial2.read();
  }
}

void SensorPH::phToSerial() {
  if (Serial2.available() > 0) {
    String sensorString = "";
    sensorString.reserve(30);
    char inChar;
    while (Serial2.peek() != '\r') {
      inChar= (char)Serial2.read();
      sensorString += inChar;
    }
    Serial2.read();   // discard <CR>
    Serial.println(sensorString);
  }
}