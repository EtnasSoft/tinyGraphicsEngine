#ifndef PLAYER_H
#define PLAYER_H

struct Player {
  int x,
    y,
    speed;
};

void player_createPlayer(int initPlayerX, int initPlayerY, int initPlayerSpeed);

void player_readControls(void);
void player_movePlayerUp(void);
void player_movePlayerDown(void);

struct Player player_getPlayer(void);

#endif // PLAYER_H
