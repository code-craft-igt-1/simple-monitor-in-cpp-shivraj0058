#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, AllVitalsOK) {
  ASSERT_FALSE(vitalsOk(99, 102, 70));
}

TEST(Monitor, BodyTemperatureOutOfRange) {
  // high temperature
  ASSERT_FALSE(vitalsOk(110, 65, 87));

  // low temperature
  ASSERT_FALSE(vitalsOk(94, 65, 87));
}

TEST(Monitor, PulseRateOutOfRange) {
  // low pulse rate
  ASSERT_FALSE(vitalsOk(99, 55, 87));

  // high pulse rate
  ASSERT_FALSE(vitalsOk(99, 110, 87));
}

TEST(Monitor, SPO2OutOfRange) {
  ASSERT_FALSE(vitalsOk(99, 99, 89));
  ASSERT_FALSE(vitalsOk(99, 99, 101));
}
