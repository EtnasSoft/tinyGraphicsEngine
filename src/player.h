#ifndef GRAPHICSENGINECLION_PLAYER_H
#define GRAPHICSENGINECLION_PLAYER_H

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

#endif // GRAPHICSENGINECLION_PLAYER_H
