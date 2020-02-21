#ifndef EMULATOR_H
#define EMULATOR_H

#include "Types.h"

void emulatorPrintEngineData(int iScrollX, int iScrollY, byte bXOff, byte bYOff, int ty);
void emulatorPrintRow(byte data[], int dataLength, byte y);
void emulatorPrintPlayFieldRow(byte row, byte bPlayfield[]);
void emulatorPrintPlayField(byte bPlayfield[]);
void emulatorPrintDemoMessage();
void cls();

#endif // EMULATOR_H
