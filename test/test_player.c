#include "../vendor/ceedling/vendor/unity/src/unity.h"
#include "unity.h"
#include "player.h"
#include "mock_gpio.h"

int initPlayerX,
    initPlayerY,
    initPlayerSpeed;

int BUTTON_UP = 1,
    BUTTON_DOWN = 2,
    HIGH = 1,
    LOW = 0;

void setUp(void) {
  initPlayerX = 0;
  initPlayerY = 0;
  initPlayerSpeed = 1;

  player_createPlayer(initPlayerX, initPlayerY, initPlayerSpeed);
}

void tearDown(void) {}

void test_noButtonPressedShouldKeepsPlayerCoords (void) {
  // When
  gpio_digitalRead_ExpectAndReturn(BUTTON_UP, LOW);
  gpio_digitalRead_ExpectAndReturn(BUTTON_DOWN, LOW);

  player_readControls();

  TEST_ASSERT_EQUAL(initPlayerY, player_getPlayer().y);
  TEST_ASSERT_EQUAL(initPlayerX, player_getPlayer().x);
}

void test_buttonUpShouldMovePlayerToUp (void) {
  // When
  gpio_digitalRead_ExpectAndReturn(BUTTON_UP, HIGH);
  gpio_digitalRead_ExpectAndReturn(BUTTON_DOWN, LOW);

  player_readControls();

  TEST_ASSERT_EQUAL(initPlayerY + initPlayerSpeed, player_getPlayer().y);
  TEST_ASSERT_EQUAL(initPlayerX, player_getPlayer().x);
}

void test_buttonDownShouldMovePlayerToDown (void) {
  // When
  gpio_digitalRead_ExpectAndReturn(BUTTON_UP, LOW);
  gpio_digitalRead_ExpectAndReturn(BUTTON_DOWN, HIGH);

  player_readControls();

  TEST_ASSERT_EQUAL(initPlayerY - initPlayerSpeed, player_getPlayer().y);
  TEST_ASSERT_EQUAL(initPlayerX, player_getPlayer().x);
}
