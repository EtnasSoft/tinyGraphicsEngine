#ifndef EMULATOR_H
#define EMULATOR_H
typedef uint8_t byte;

void PrintRow(byte data[], int dataLength, byte y);
void PrintPlayFieldRow(byte row);
void PrintPlayField();
void PrintDemoMessage();
void cls();

#endif // EMULATOR_H
