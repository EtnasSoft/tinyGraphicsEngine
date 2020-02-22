#include <stdio.h>

#include "Types.h"
#include "i2c.h"
//#include <Arduino.h>
//#include <avr/interrupt.h>

void i2cBegin(byte screenSlaveAddress) {
//  I2CPORT |= ((1 << SSD1306_SDA) + (1 << SSD1306_SCL));
//  I2CDDR |= ((1 << SSD1306_SDA) + (1 << SSD1306_SCL));
//  I2CPORT &= ~(1 << SSD1306_SDA); // data line low first
//  delayMicroseconds(SAFE_DELAY);
//  I2CPORT &= ~(1 << SSD1306_SCL); // then clock line low is a START signal
  //i2cByteOut(addr << 1);     // send the slave address
}

void i2cEnd() {}

void i2cByteWrite(byte *pData, byte bLen) {}

void i2cWrite(byte *buf, byte len, byte screenSlaveAddress) {
  i2cBegin(screenSlaveAddress);
  i2cByteWrite(buf, len);
  i2cEnd();
}

void i2cWriteData(byte *buf, byte len, byte screenSlaveAddress) {
  i2cBegin(screenSlaveAddress);
  i2cByteOut(0x40);
  i2cByteWrite(buf, len);
  i2cEnd();
}

void i2cByteOut(byte b) {

}
