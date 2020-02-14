#include "../vendor/ceedling/vendor/unity/src/unity.h"
#include "unity.h"
#include "helpers.h"

void setUp(void) {}

void tearDown(void) {}

void test_MinShouldReturnTheMinInteger(void) {
  int a, b, expected;
  a = 10;
  b = 20;
  expected = a;

  TEST_ASSERT_EQUAL_INT(expected, MIN(a, b));
  TEST_ASSERT_EQUAL_INT(expected, MIN(b, a));
}

void test_MaxShouldReturnTheMaxInteger(void) {
  int a, b, expected;
  a = 10;
  b = 20;
  expected = b;

  TEST_ASSERT_EQUAL_INT(expected, MAX(a, b));
  TEST_ASSERT_EQUAL_INT(expected, MAX(b, a));
}

void test_MinAndMaxShouldReturnTheSameValueWhenDuplicated(void) {
  int a, b, expected;
  a = b = 10;
  expected = 10;

  TEST_ASSERT_EQUAL_INT(expected, MIN(a, b));
  TEST_ASSERT_EQUAL_INT(expected, MIN(b, a));
  TEST_ASSERT_EQUAL_INT(expected, MAX(a, b));
  TEST_ASSERT_EQUAL_INT(expected, MAX(b, a));
}
