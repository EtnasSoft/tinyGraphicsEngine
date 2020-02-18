#include "../vendor/ceedling/vendor/unity/src/unity.h"
#include "unity.h"
#include "screenInterface.h"
#include "screenParams.h"
#include <string.h>

#include "mock_i2c.h"

//const int SCREEN_SLAVE_ADDRESS = 0x3C;

const byte FLIP = 0;
const byte INVERT = 0;

void setUp(void) {}

void tearDown(void) {}

void test_screenInitShouldCallToI2CModuleForSetupTheScreen() {
  // When
  i2cWrite_Expect(0, 0, SCREEN_SLAVE_ADDRESS);
  i2cWrite_IgnoreArg_buf();
  i2cWrite_IgnoreArg_len();

  screenInit(FLIP, INVERT);
}

void test_screenWriteShouldCallToI2CModule() {
  unsigned char seq[] = {
      0x00,       // Starting to send a commands sequence or script
      0xAE,       // Display off
      0xA8, 0x3F  // Set MUX Ratio 0x3F = 63; 0-63 (64) rows
  };

  // When
  i2cWrite_ExpectWithArray(seq, sizeof(seq), sizeof(seq), SCREEN_SLAVE_ADDRESS);

  screenWrite(seq, sizeof(seq));
}

void test_screenSetPositionZeroZeroShouldSetupTheCorrectCoordsForWrite() {
  unsigned char buf1[2], buf2[2], buf3[2];
  int xPos, yPos;

  xPos = 0;
  yPos = 0;

  buf1[0] = 0x00;
  buf1[1] = 0xb0 | yPos;

  i2cWrite_ExpectWithArray(buf1, sizeof(buf1), sizeof(buf1), SCREEN_SLAVE_ADDRESS);

  buf2[0] = 0x00;
  buf2[1] = 0x00 | (xPos & 0xf);
  i2cWrite_ExpectWithArray(buf2, sizeof(buf2), sizeof(buf2), SCREEN_SLAVE_ADDRESS);

  buf3[0] = 0x00;
  buf3[1] = 0x10 | ((xPos >> 4) & 0xf);
  i2cWrite_ExpectWithArray(buf3, sizeof(buf3), sizeof(buf3), SCREEN_SLAVE_ADDRESS);

  screenSetPosition(xPos, yPos);
}

void test_screenSetPositionAtAnyCoordsShouldSetupTheCorrectCoordsForWrite() {
  unsigned char buf1[2], buf2[2], buf3[2];
  int xPos, yPos;

  xPos = 30;
  yPos = 15;

  buf1[0] = 0x00;
  buf1[1] = 0xb0 | yPos;

  i2cWrite_ExpectWithArray(buf1, sizeof(buf1), sizeof(buf1), SCREEN_SLAVE_ADDRESS);

  buf2[0] = 0x00;
  buf2[1] = 0x00 | (xPos & 0xf);
  i2cWrite_ExpectWithArray(buf2, sizeof(buf2), sizeof(buf2), SCREEN_SLAVE_ADDRESS);

  buf3[0] = 0x00;
  buf3[1] = 0x10 | ((xPos >> 4) & 0xf);
  i2cWrite_ExpectWithArray(buf3, sizeof(buf3), sizeof(buf3), SCREEN_SLAVE_ADDRESS);

  screenSetPosition(xPos, yPos);
}

void test_screenFillShouldOverrideScreenWithAnyByteProvided() {
  unsigned char byteForFill = 0xff;
  unsigned char expected[SCREEN_WIDTH];
  memset(expected, byteForFill, SCREEN_WIDTH);

  // 8 times (or same as SCREEN_HEIGHT)
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);

  i2cWrite_Ignore();

  screenFill(byteForFill);
}

void test_screenClearShouldOverrideScreenWithBlankValues() {
  unsigned char clearChar = 0x00;
  unsigned char expected[SCREEN_WIDTH];
  memset(expected, clearChar, SCREEN_WIDTH);

  // 8 times (or same as SCREEN_HEIGHT)
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  i2cWriteData_ExpectWithArray(expected, SCREEN_WIDTH, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);

  i2cWrite_Ignore();

  screenClear();
}

void test_screenWriteCommandShouldSendTheCorrectSequence() {
  unsigned char buf[2];
  unsigned char myCommand = 0x10;

  buf[0] = 0x00;
  buf[1] = myCommand;

  i2cWrite_ExpectWithArray(buf, sizeof(buf), sizeof(buf), SCREEN_SLAVE_ADDRESS);

  screenWriteCommand(myCommand);
}

void test_screenWriteCommand2ShouldSendTheCorrectSequence() {
  unsigned char buf[3];
  unsigned char command1 = 0x10,
    command2 = 0x20;

  buf[0] = 0x00;
  buf[1] = command1;
  buf[2] = command2;

  i2cWrite_ExpectWithArray(buf, sizeof(buf), sizeof(buf), SCREEN_SLAVE_ADDRESS);

  screenWriteCommand2(command1, command2);
}

void test_screenShutdownShouldSendTheCorrectCommandsToScreen() {
  unsigned char shutdownSeq[2] = {
      0x00,
      0xaE
  };

  // When
  i2cWrite_ExpectWithArray(shutdownSeq, sizeof(shutdownSeq), sizeof(shutdownSeq), SCREEN_SLAVE_ADDRESS);

  screenShutdown();
}

void test_screenSetContrastShouldSendTheCorrectCommandsToScreen() {
  char newContrast = 0xff;

  unsigned char contrastSeq[3];
  contrastSeq[0] = 0x00;
  contrastSeq[1] = 0x81;
  contrastSeq[2] = newContrast;  // New contrast value

  // When
  i2cWrite_ExpectWithArray(contrastSeq, sizeof(contrastSeq), sizeof(contrastSeq), SCREEN_SLAVE_ADDRESS);

  screenSetContrast(newContrast);
}
