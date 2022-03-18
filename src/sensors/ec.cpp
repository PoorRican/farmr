//
// Created by Josue Figueroa on 12/13/20.
//

#include "sensors/ec.h"

SensorEC::SensorEC(const uint8_t &pin) : Sensor(pin), ec(0) {}

Sensor::SensName SensorEC::getType() const {
  return Sensor::Ec;
}

void SensorEC::init() {
  // Open communication
  Serial3.begin(38400);
  Serial3.print("E\r");
  setContinuous();
}

void SensorEC::update() {
#ifndef SENSORLESS_OPERATION
  if (!isCalibrating) {
    if (Serial3.available() > 0) {
      uint16_t res = Serial3.parseInt();
      clearECBuffer();
      ec = res;
    }
    ec = 0;
  }
#endif
}

double SensorEC::get() const {
  return ec;
}

void SensorEC::calibrating(boolean c) {
  isCalibrating = c;
}

void SensorEC::reset() {
  clearECBuffer();
  Serial3.print("X\r");
  delay(2750);
  ecToSerial();
}

void SensorEC::getInfo() {
  clearECBuffer();
  Serial3.print("I\r");
  delay(1450);
  ecToSerial();
}

void SensorEC::setLed(boolean state) {
  state ? Serial3.print("L1\r") : Serial3.print("L0\r");
}

void SensorEC::setContinuous() {
  Serial3.print("C\r");
}

void SensorEC::setStandby() {
  Serial3.print("E\r");
}

void SensorEC::setProbeType() {
  Serial3.print("P,2\r");
}

void SensorEC::setDry() {
  Serial3.print("Z0\r");
}

void SensorEC::setFortyThousand() {
  Serial3.print("Z40\r");
#ifdef VERBOSE_OUTPUT
  Serial.println("Calibrating EC Sensor to 10,000 uS");
#endif
}

void SensorEC::setTenThousand() {
  Serial3.print("Z10\r");
#ifdef VERBOSE_OUTPUT
  Serial.println("Calibrating EC Sensor to 40,000 uS");
#endif
}

void SensorEC::adjustTemp(double temp) const {
  if (temp != 0 && !isCalibrating) {
    char tempArray[4];
    dtostrf(temp, 4, 2, tempArray);
    String command = (String)tempArray + ",C\r";
    Serial3.print(command);
  }
}

void SensorEC::clearECBuffer() {
  while (Serial3.available() > 0) {
    Serial3.read();
  }
}

void SensorEC::ecToSerial() {
  if (Serial3.available() > 0) {
    String sensorString = "";
    sensorString.reserve(30);
    char inChar;
    while (Serial3.peek() != '\r') {
      inChar = (char)Serial3.read();
      sensorString += inChar;
    }
    Serial3.read();     // discard <CR>
    Serial.println(sensorString);
  }
}