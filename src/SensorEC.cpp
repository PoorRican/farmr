//
// Created by Josue Figueroa on 12/13/20.
//

#include "SensorEC.h"

SensorEC::SensorEC(const int &pin, SoftwareSerial *serial)
: Sensor(pin), serial(serial) {
  for (uint8_t i = 0; i < sample_size; i++ ) {
    readings[i] = 0;
  }
}

Sensor::SensName SensorEC::getType() const {
  return Sensor::Ec;
}

void SensorEC::init() {
  // Open communication
  serial->begin(38400);
  serial->print("E\r");
  setContinuous();
}

void SensorEC::update() {
  readings[sample_counter++] = getRaw();
  sample_counter = sample_counter % sample_size;
  smooth();
}

void SensorEC::fastUpdate() {
  uint16_t e = getRaw();
  for (uint8_t i = 0; i < sample_size; i++) {
    readings[i] = e;
  }
  smooth();
}

uint16_t SensorEC::get() const {
  return ec;
}

uint16_t SensorEC::getRaw() const {
  if (!isCalibrating) {
    if (serial->available() > 0) {
      uint16_t res = serial->parseInt();
      clearECBuffer();
      return res;
    }
    return 0;
  }
  else {
    return ec;
  }
}

void SensorEC::calibrating(boolean c) {
  isCalibrating = c;
}

void SensorEC::reset() {
  clearECBuffer();
  serial->print("X\r");
  delay(2750);
  ecToSerial();
}

void SensorEC::getInfo() {
  clearECBuffer();
  serial->print("I\r");
  delay(1450);
  ecToSerial();
}

void SensorEC::setLed(boolean state) {
  state ? serial->print("L1\r") : serial->print("L0\r");
}

void SensorEC::setContinuous() {
  serial->print("C\r");
}

void SensorEC::setStandby() {
  serial->print("E\r");
}

void SensorEC::setProbeType() {
  serial->print("P,2\r");
}

void SensorEC::setDry() {
  serial->print("Z0\r");
}

void SensorEC::setFortyThousand() {
  serial->print("Z40\r");
}

void SensorEC::adjustTemp(float temp) {
  if (temp != 0 && !isCalibrating) {
    char tempArray[4];
    dtostrf(temp, 4, 2, tempArray);
    String command = (String)tempArray + ",C\r";
    serial->print(command);
  }
}

void SensorEC::smooth() {
  uint16_t res = 0;
  for (uint8_t i = 0; i < sample_counter; i++) {
    res += readings[i];
  }
  ec = (uint16_t)(res / sample_counter);
}

void SensorEC::ecToSerial() {
  if (serial->available() > 0) {
    String sensorString = "";
    sensorString.reserve(30);
    char inChar;
    while (serial->peek() != '\r') {
      inChar = (char)serial->read();
      sensorString += inChar;
    }
    serial->read();     // discard <CR>
    Serial.println(sensorString);
  }
}