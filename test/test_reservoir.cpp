//
// Created by Josue Figueroa on 12/12/20.
//

#if defined(ARDUINO)

#include <Arduino.h>
#include <unity.h>

#include "reservoir.h"

Ultrasonic dummy(15);
Reservoir* r;

void setUp() {
  r = new Reservoir(&dummy);
}


void test_calibrate_empty() {
  unsigned int num = 10;
  r->calibrateEmpty(num);
  TEST_ASSERT_EQUAL_INT(num, r->getEmpty());
}

void test_calibrate_full() {
  unsigned int num = 100;
  r->calibrateFull(num);
  TEST_ASSERT_EQUAL_INT(num, r->getFull());
}

void test_above_threshold() {
  unsigned int empty = 10;
  unsigned int full = 110;

  r->calibrateEmpty(empty);
  r->calibrateFull(full);

  TEST_ASSERT_EQUAL_DOUBLE(0.25, r->getThreshold());
  TEST_ASSERT_TRUE(r->measure_volume(25))
  TEST_ASSERT_FALSE(r->measure_volume(85))
  TEST_ASSERT_FALSE(r->measure_volume(90))
}

void test_measure_volume() {
  unsigned int empty = 10;
  unsigned int full = 110;

  r->calibrateEmpty(empty);
  r->calibrateFull(full);

  TEST_ASSERT_EQUAL(0.75, r->measure_volume(85));
  TEST_ASSERT_EQUAL(0.5, r->measure_volume(60));
  TEST_ASSERT_EQUAL(0.25, r->measure_volume(35));
}


void setup() {
  delay(2000);

  UNITY_BEGIN();

  RUN_TEST(test_calibrate_empty);
  RUN_TEST(test_calibrate_full);
  RUN_TEST(test_above_threshold);
  RUN_TEST(test_measure_volume);

  UNITY_END();
}

#endif


