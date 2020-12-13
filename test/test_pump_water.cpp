//
// Created by Josue Figueroa on 12/12/20.
//

#include <unity.h>
#include "pump.h"

Ultrasonic dummy(15);
Reservoir *r;
Pump *p;

const int dummy_pin = 15;


void setUp() {
  r = new Reservoir(&dummy);
  p = new Pump(dummy_pin, r);
}

void test_frequencySetterGetter() {
  int freq = 0;
  TEST_ASSERT_FALSE(p->setFrequency(freq));
  freq = 13;
  TEST_ASSERT_FALSE(p->setFrequency(freq));

  freq = 1;
  TEST_ASSERT_TRUE(p->setFrequency(freq));
  TEST_ASSERT_EQUAL(freq, p->getFrequency());

  freq = 12;
  TEST_ASSERT_TRUE(p->setFrequency(freq));
  TEST_ASSERT_EQUAL(freq, p->getFrequency());
}

void test_floodTimeSetterGetter() {
  int time = 0;
  TEST_ASSERT_FALSE(p->setFloodTime(time));
  time = 13;
  TEST_ASSERT_FALSE(p->setFrequency(time));

  time = 1;
  TEST_ASSERT_TRUE(p->setFloodTime(time));
  TEST_ASSERT_EQUAL(time, p->getFloodTime());

  time = 12;
  TEST_ASSERT_TRUE(p->setFloodTime(time));
  TEST_ASSERT_EQUAL(time, p->getFloodTime());
}

void test_calcNextCycleTime() {
  int hour = 7;

  int freq = 2;
  p->setFrequency(freq);
  TEST_ASSERT_EQUAL_INT(1, p->calcNextCycleTime(hour));
  freq = 4;
  p->setFrequency(freq);
  TEST_ASSERT_EQUAL_INT(1, p->calcNextCycleTime(hour));
  freq = 8;
  p->setFrequency(freq);
  TEST_ASSERT_EQUAL_INT(1, p->calcNextCycleTime(hour));

  freq = 6;
  p->setFrequency(freq);
  TEST_ASSERT_EQUAL_INT(5, p->calcNextCycleTime(hour));
  hour = 11;
  TEST_ASSERT_EQUAL_INT(1, p->calcNextCycleTime(hour));

  hour = 12;
  freq = 2;
  p->setFrequency(freq);
  TEST_ASSERT_EQUAL_INT(0, p->calcNextCycleTime(hour));
  hour = 12;
  freq = 4;
  p->setFrequency(freq);
  TEST_ASSERT_EQUAL_INT(6, p->calcNextCycleTime(hour));
  hour = 18;
  TEST_ASSERT_EQUAL_INT(0, p->calcNextCycleTime(hour));
}

void test_getPin() {
  TEST_ASSERT_EQUAL(dummy_pin, p->getPin());
}

void test_startWatering() {
  unsigned int empty = 10;
  unsigned int full = 110;

  r->calibrateEmpty(empty);
  r->calibrateFull(full);
}


void loop() {
  UNITY_BEGIN();

  RUN_TEST(test_calcNextCycleTime);
  RUN_TEST(test_floodTimeSetterGetter);
  RUN_TEST(test_frequencySetterGetter);
  RUN_TEST(test_getPin);

  UNITY_END();
}