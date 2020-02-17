#ifndef GRAPHICSENGINECLION_I2C_H
#define GRAPHICSENGINECLION_I2C_H

#include <stdint.h>
typedef uint8_t byte;

//void i2cStart(byte addr);
//void i2cStop();
//void i2cByteWrite(byte *pData, byte bLen);

static inline void i2cByteOut(byte b);


// Wrappers
void i2cWrite(byte *buf, int len, int screenSlaveAddress);
void i2cWriteData(byte *buf, int len, int screenSlaveAddress);

#endif // GRAPHICSENGINECLION_I2C_H
