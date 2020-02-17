#ifndef GRAPHICSENGINECLION_SCREENINTERFACE_H
#define GRAPHICSENGINECLION_SCREENINTERFACE_H

typedef uint8_t byte;

void screenInit(byte flip, byte invert);
void screenWrite(unsigned char *buf, size_t len);
void screenSetPosition(int x, int y);
void screenFill(unsigned char ucData);
void screenClear(void);
void screenWriteCommand(unsigned char c);
void screenWriteCommand2(unsigned char c, unsigned char d);
void screenShutdown();
void screenSetContrast(unsigned char ucContrast);


#endif // GRAPHICSENGINECLION_SCREENINTERFACE_H
