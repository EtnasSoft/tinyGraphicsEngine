
#ifndef ENGINE_H
#define ENGINE_H
typedef uint8_t byte;

int main2();
void DrawShiftedChar(byte *s1, byte *s2, byte *d, byte bXOff, byte bYOff);
void DrawPlayField(int bScrollX, int bScrollY);
void reloadPlayField();
void adjustPlayField();

#endif // ENGINE_H
