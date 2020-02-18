#include <stdio.h>
#include <stdint.h>
#include "i2c.h"

typedef uint8_t byte;

void i2cStart(byte screenSlaveAddress) {}
void i2cStop() {}
void i2cByteWrite(byte *pData, byte bLen) {}

void i2cWrite(byte *buf, byte len, byte screenSlaveAddress) {
  i2cStart(screenSlaveAddress);
  i2cByteWrite(buf, len);
  i2cStop();
}

void i2cWriteData(byte *buf, byte len, byte screenSlaveAddress) {}

