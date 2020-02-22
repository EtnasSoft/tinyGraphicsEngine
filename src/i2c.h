#ifndef GRAPHICSENGINECLION_I2C_H
#define GRAPHICSENGINECLION_I2C_H

#include "Types.h"

void i2cBegin(byte addr);
void i2cEnd();
void i2cByteWrite(byte *pData, byte bLen);

void i2cByteOut(byte b);


// Wrappers
void i2cWrite(byte *buf, byte len, byte screenSlaveAddress);
void i2cWriteData(byte *buf, byte len, byte screenSlaveAddress);

#endif // GRAPHICSENGINECLION_I2C_H
