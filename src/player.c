#include "player.h"
#include "gpio.h"

const int ButtonA = 1;
const int ButtonB = 2;
struct Player player;

void player_createPlayer(int initPlayerX, int initPlayerY, int initPlayerSpeed) {
  player.x = initPlayerX;
  player.y = initPlayerY;
  player.speed = initPlayerSpeed;
}

struct Player player_getPlayer(void) {
  return player;
}

void player_readControls() {
  if (gpio_digitalRead(ButtonA)) {
    player_movePlayerUp();
  }

  if (gpio_digitalRead(ButtonB)) {
    player_movePlayerDown();
  }
}

void player_movePlayerUp() {
  player.y += player.speed;
}

void player_movePlayerDown() {
  player.y -= player.speed;
}
