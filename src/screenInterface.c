#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "screenInterface.h"
#include "screenParams.h"
#include "i2c.h"

// Command registers:
// TODO: Apply this registers to init sequence...
//#define SSD1306_SETCONTRAST 		0x81
//#define SSD1306_DISPLAYALLON_RESUME 	0xA4
//#define SSD1306_DISPLAYALLON 		0xA5
//#define SSD1306_NORMALDISPLAY 		0xA6
//#define SSD1306_INVERTDISPLAY 		0xA7
//#define SSD1306_DISPLAYOFF 		0xAE
//#define SSD1306_DISPLAYON 		0xAF
//#define SSD1306_SETDISPLAYOFFSET 	0xD3
//#define SSD1306_SETCOMPINS 		0xDA
//#define SSD1306_SETVCOMDETECT 		0xDB
//#define SSD1306_SETDISPLAYCLOCKDIV 	0xD5
//#define SSD1306_SETPRECHARGE 		0xD9
//#define SSD1306_ENABLE_CHARGE_PUMP	0x8D
//#define SSD1306_SETMULTIPLEX 		0xA8
//#define SSD1306_SETSTARTLINE 		0x40
//#define SSD1306_MEMORYMODE 		0x20
//#define SSD1306_HV_COLUMN_ADDRESS	0x21
//#define SSD1306_HV_PAGE_ADDRESS		0x22
//#define SSD1306_PAM_PAGE_START		0xB0
//#define SSD1306_COMSCANDEC 		0xC8
//#define SSD1306_SEGREMAP 		0xA0

// TODO: flip and invert must be properties of an objectm setted in a constructor.
void screenInit(byte flip, byte invert) {

  unsigned char seq[] = {
      0x00,       // Starting to send a commands sequence or script
      0xAE,       // Display off
      0xA8, 0x3F, // Set MUX Ratio 0x3F = 63; 0-63 (64) rows
      0xD3, 0x00, // Set display offset to 0
      0x40,       // Set Display Start Line to 0
      0xA1,       // Scan direction AXIS X: [0xA0, 0xA1]
      0xC8,       // Scan direction AXIS Y (invert screen): [0xC0, 0xC8]
      0xDA, 0x12, // Mapping COM pins
      0x81, 0xAA, // Setting constrast control
      0xA4,       // Disable Entire Display ON (GDDRAM)
      0xA6,       // Set normal display mode
      0xD5, 0x80, // Set OSC Frequency
      0x8D, 0x14, // Enable charge pump regulator
      0xAF,       // Set display on

      /*0x21, 0x00, 0x7f, 0x22, 0x00, 0x07,*/

      0x20, 0x02  // Set memory addressing mode [0x00 - Horizontal, 0x01 - Verticial, 0x02 - Page]
  };

  screenWrite(seq, sizeof(seq));
}

void screenWrite(unsigned char *buf, size_t len) {
  i2cWrite(buf, len, SCREEN_SLAVE_ADDRESS);
}

void screenWriteCommand(unsigned char c) {
  unsigned char buf[2];

  buf[0] = 0x00; // command introducer
  buf[1] = c;
  i2cWrite(buf, 2, SCREEN_SLAVE_ADDRESS);
}

void screenWriteCommand2(unsigned char c, unsigned char d) {
  unsigned char buf[3];

  buf[0] = 0x00;
  buf[1] = c;
  buf[2] = d;
  i2cWrite(buf, 3, SCREEN_SLAVE_ADDRESS);
}

void screenShutdown() {
  screenWriteCommand(0xaE); // turn off OLED
}

void screenSetContrast(unsigned char ucContrast) {
  screenWriteCommand2(0x81, ucContrast);
}

void screenSetPosition(int x, int y) {
  screenWriteCommand(0xb0 | y);                // go to page Y
  screenWriteCommand(0x00 | (x & 0xf));        // lower col addr
  screenWriteCommand(0x10 | ((x >> 4) & 0xf)); // upper col addr
}

void screenFill(unsigned char ucData) {
  int x;
  unsigned char temp[SCREEN_WIDTH];

  memset(temp, ucData, SCREEN_WIDTH);
  for (x = 0; x < VIEWPORT_HEIGHT; x++) {
    screenSetPosition(0, x);
    i2cWriteData(temp, SCREEN_WIDTH, SCREEN_SLAVE_ADDRESS);
  }
}

void screenClear(void) {
  screenFill(0x00);
}
