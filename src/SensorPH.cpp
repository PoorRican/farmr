//
// Created by Josue Figueroa on 12/13/20.
//

#include "SensorPH.h"

SensorPH::SensorPH(const int &pin, SoftwareSerial* serial) : Sensor(pin) {
  for (uint8_t i = 0; i < sample_size; i++) {
    readings[i] = 0;
  }
}

SensorPH::SensorPH(const SensorPH &other) : Sensor(other) {
  sample_counter = other.sample_counter;
  for (uint8_t i = 0; i < sample_size; i++) {
    readings[i] = 0;
  }
  pH = other.pH;
}

SensorPH& SensorPH::operator=(const SensorPH &other) {
  sample_counter = other.sample_counter;
  for (uint8_t i = 0; i < sample_size; i++) {
    readings[i] = 0;
  }
  pH = other.pH;
  return *this;
}

Sensor::SensName SensorPH::getType() const {
  return Sensor::pH;
}

void SensorPH::init() {
  // Begin communication
  serial->begin(38400);
  // reading on-demand mode
  serial->print("E\r");
  // make a reading to allow `fastUpdate` to work
  serial->print("R\r");
}

void SensorPH::update() {
  readings[sample_counter++] = getRaw();
  sample_counter = sample_counter % sample_size;
  smooth();
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
    serial->print("R\r");
    if (serial->available() > 0) {
      float res = serial->parseFloat();
      serial->read();
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
  serial->print("I\r");
  delay(10);
  phToSerial();
}

void SensorPH::getInfo() {
  clearBuffer();
  serial->print("I\r");
  delay(10);
  phToSerial();
}

void SensorPH::setLed(boolean state) {
  (state) ? serial->print("L1\r") : serial->print("L0\r");
}

void SensorPH::setContinuous() {
  serial->print("C\r");
}

void SensorPH::setStandby() {
  serial->print("E\r");
}

void SensorPH::setFour() {
  serial->print("F\r");
}

void SensorPH::setSeven() {
  serial->print("T\r");
}

void SensorPH::setTen() {
  serial->print("T\r");
}

void SensorPH::adjustTemp(float temp) {
  if (temp != 0 && !isCalibrating) {
    char tempArray[4];
    dtostrf(temp, 4, 2, tempArray);
    String command = (String)tempArray + "\r";
    serial->print(command);
  }
}

void SensorPH::smooth() {
  float res = 0;
  for (uint8_t i = 0; i < sample_size; i++) {
    res += readings[i];
  }
  pH = (float)(res / sample_size);
}

void SensorPH::clearBuffer() {
  while (serial->available() > 0) {
    serial->read();
  }
}

void SensorPH::phToSerial() {
  if (serial->available() > 0) {
    String sensorString = "";
    sensorString.reserve(30);
    char inChar;
    while (serial->peek() != '\r') {
      inChar= (char)serial->read();
      sensorString += inChar;
    }
    serial->read();   // discard <CR>
    Serial.println(sensorString);
  }
}