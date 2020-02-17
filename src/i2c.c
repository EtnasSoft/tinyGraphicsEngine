#include <stdint.h>
#include "i2c.h"

typedef uint8_t byte;

void i2cStart(byte addr) {}
void i2cStop() {}
void i2cByteWrite(byte *pData, byte bLen) {}

void i2cWrite(byte *buf, int len, int screenSlaveAddress) {}
  i2cStart(screenSlaveAddress);
  i2cByteWrite(buf, len);
  i2cStop();
}

void i2cWriteData(byte *buf, int len, int screenSlaveAddress) {}

