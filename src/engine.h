
#ifndef GRAPHICSENGINECLION_ENGINE_H
#define GRAPHICSENGINECLION_ENGINE_H

#include "Types.h"

int engineStart();
void engineDrawShiftedChar(byte *s1, byte *s2, byte *d, byte bXOff, byte bYOff);
void engineDrawPlayField(int bScrollX, int bScrollY);
void engineReloadPlayField();
void engineAdjustPlayField();

#endif // GRAPHICSENGINECLION_ENGINE_H
