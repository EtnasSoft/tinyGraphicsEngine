#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../lib/conio/conio.h"

#include "screenParams.h"
#include "assets.h"
#include "engine.h"
#include "emulator.h"


// DEFS
// ------------------------------------------------------------------
typedef uint8_t byte;

#define DEBUG
#define INCREASE 43 // ASCII CODE for +
#define DECREASE 45 // ASCII CODE for -


// CONSTS
// ------------------------------------------------------------------
static byte bPlayfield[PLAYFIELD_ROWS * PLAYFIELD_COLS];
static int iScrollX, iScrollY;


// MAIN
// ------------------------------------------------------------------
int engineStart(void) {
#ifdef DEBUG
  cls();
#endif

  // Init the screen position and load the tilemap accordingly
  iScrollX = 0;
  iScrollY = 232;
  engineReloadPlayField();

  engineDrawPlayField(iScrollX, iScrollY);
  emulatorPrintDemoMessage();

  // DEMO FUNCTIONALITY
  char ch = 0, flag = 0;

  while (1) {
    ch = c_getch();

    if (ch == 13) { // RETURN
      break;
    }

    if (ch == 119) { // W (UP)
      iScrollY++;
      flag = 1;
    }

    if (ch == 115) { // S (DOWN)
      iScrollY--;
      flag = 1;
    }

    if (ch == 100) { // D (RIGHT)
      iScrollX++;
      flag = 1;
    }

    if (ch == 97) { // A (LEFT)
      iScrollX--;
      flag = 1;
    }

    if (flag) {
      // Limits
      iScrollX = (iScrollX >= PLAYFIELD_COLS * MODULE) ? 0 :
                 (iScrollX < 0) ? ((PLAYFIELD_COLS * MODULE) - 1) : iScrollX;

      if (iScrollY >= 240) {
        iScrollY = 8;
        engineReloadPlayField();
      } else if (iScrollY < 0) {
        iScrollY = 232;
        engineReloadPlayField();
      }

      cls();
      engineDrawPlayField(iScrollX, iScrollY);
      emulatorPrintDemoMessage();
    }
  }

  return 0;
}

void engineDrawShiftedChar(byte *s1, byte *s2, byte *d, byte bXOff, byte bYOff) {
  byte c, c2, z;

  for (z = 0; z < (8 - bXOff); z++) {
    c = *s1++; // pgm_read_byte(s1++);
    c >>= bYOff; // shift over
    c2 = *s2++; // pgm_read_byte(s2++);
    c2 <<= (8 - bYOff);
    *d++ = (c | c2);
  }
}

void engineDrawPlayField(int bScrollX, int bScrollY) {
  byte x, y, tx, c, *s, *sNext, *d,
      bTemp[SCREEN_WIDTH];

  int ty, bXOff, bYOff, iOffset, iOffset2, cIndex, cIndex2;

  bXOff = bScrollX & (MODULE - 1);
  bYOff = bScrollY & (MODULE - 1);

  ty = (bScrollY >> 3) + (EDGES / 2);

#ifdef DEBUG
  emulatorPrintEngineData(iScrollX, iScrollY, bXOff, bYOff, ty);
#endif

  engineAdjustPlayField();

  // draw the 8 rows
  for (y = 0; y < VIEWPORT_HEIGHT; y++) {
    memset(bTemp, 0, sizeof(bTemp));

    if (ty >= PLAYFIELD_ROWS) {
      ty -= PLAYFIELD_ROWS;
    }

    tx = (bScrollX >> 3) + (EDGES / 2);

    // Draw the playfield characters at the given scroll position
    d = bTemp;

    if (bYOff) {
      for (x = 0; x < VIEWPORT_WIDTH; x++) {
        if (tx >= PLAYFIELD_COLS) {
          tx -= PLAYFIELD_COLS; // wrap around
        }

        iOffset = tx + (ty * PLAYFIELD_COLS);
        iOffset2 = (iOffset + PLAYFIELD_COLS); // next line

        if (iOffset2 >= (PLAYFIELD_ROWS * PLAYFIELD_COLS)) {    // past bottom
          iOffset2 -= (PLAYFIELD_ROWS * PLAYFIELD_COLS);
        }

        cIndex = iOffset % (PLAYFIELD_ROWS * PLAYFIELD_COLS);
        c = bPlayfield[cIndex];
        s = (byte *)&ucTiles[(c * MODULE) + bXOff];

        cIndex2 = iOffset2 % (PLAYFIELD_ROWS * PLAYFIELD_COLS);
        c = bPlayfield[cIndex2];
        sNext = (byte *)&ucTiles[(c * MODULE) + bXOff];

        engineDrawShiftedChar(s, sNext, d, bXOff, bYOff);

        d += (MODULE - bXOff);
        bXOff = 0;
        tx++;
      }

      // partial character left to draw
      if (d != &bTemp[SCREEN_WIDTH]) {
        bXOff = (byte)(&bTemp[SCREEN_WIDTH] - d);

        if (tx >= PLAYFIELD_COLS) {
          tx -= PLAYFIELD_COLS;
        }

        iOffset = tx + ty * PLAYFIELD_COLS;
        iOffset2 = iOffset + PLAYFIELD_COLS; // next line

        if (iOffset2 >= (PLAYFIELD_ROWS * PLAYFIELD_COLS)) {    // past bottom
          iOffset2 -= (PLAYFIELD_ROWS * PLAYFIELD_COLS);
        }

        c = bPlayfield[iOffset];
        s = (byte *)&ucTiles[c * MODULE];
        c = bPlayfield[iOffset2];
        sNext = (byte *)&ucTiles[c * MODULE];
        engineDrawShiftedChar(s, sNext, d, MODULE - bXOff, bYOff);
      }
      // simpler case of vertical offset of 0 for each character
    } else {
      //-----------------------------------
      // NON BYOFF; SCREEN BYTE COMPLETED!
      //-----------------------------------

      // Filling each col of the SCREEN_WIDTH
      for (x = 0; x < VIEWPORT_WIDTH; x++) {
        if (tx >= PLAYFIELD_COLS) {
          tx -= PLAYFIELD_COLS;
        }

        iOffset = tx + (ty * PLAYFIELD_COLS);
        cIndex = iOffset % (PLAYFIELD_ROWS * PLAYFIELD_COLS);
        c = bPlayfield[cIndex];
        s = (byte *)&ucTiles[(c * MODULE) + bXOff];
        memcpy(d, s, MODULE - bXOff);
        d += (MODULE - bXOff);
        bXOff = 0;
        tx++;
      }

      // partial character left to draw
      if (d != &bTemp[SCREEN_WIDTH]) {
        printf("\n\nPARTIAL CHARACTER LEFT \n\n");
        bXOff = (byte)(&bTemp[SCREEN_WIDTH] - d);

        if (tx >= PLAYFIELD_COLS) {
          tx -= PLAYFIELD_COLS;
        }

        iOffset = tx + ty * PLAYFIELD_COLS;
        c = bPlayfield[iOffset];
        s = (byte *)&ucTiles[c * MODULE];
        memcpy(d, s, bXOff);
      }
    }

    // Send it to the display
    //oledSetPosition(0, y);
    //I2CWriteData(bTemp, SCREEN_WIDTH);

    ty++;
    emulatorPrintRow(bTemp, SCREEN_WIDTH, y);
  }

  emulatorPrintPlayField(bPlayfield);
}

void engineReloadPlayField() {
  byte x, y, *d, bitStart,
      iStart = iScrollY >> 3;

  for (y = 0; y < PLAYFIELD_ROWS; y++) {
    bitStart = ((iStart + y) * PLAYFIELD_COLS) % (PLAYFIELD_COLS * PLAYFIELD_ROWS);
    d = &bPlayfield[bitStart];

    for (x = 0; x < PLAYFIELD_COLS; x++) {
      memcpy(d++, &tileMap[(iStart + y) % TILEMAP_HEIGHT][x], 1);
    }
  }
}

void engineAdjustPlayField() {
  byte *d1, *d2,
      currentRow = (iScrollY >> 3) + (EDGES / 2);

  int playFieldLength = PLAYFIELD_ROWS * PLAYFIELD_COLS,
      nextPlayFieldBit = (currentRow + VIEWPORT_HEIGHT) * PLAYFIELD_COLS,
      cNextPlayFieldBit = nextPlayFieldBit % playFieldLength,
      cNextRow = (currentRow + VIEWPORT_HEIGHT) % TILEMAP_HEIGHT,
      prevPlayFieldBit = currentRow * PLAYFIELD_COLS,
      cPrevPlayFieldBit = prevPlayFieldBit % playFieldLength,
      cPrevRow = currentRow % TILEMAP_HEIGHT;

  d1 = &bPlayfield[cNextPlayFieldBit];
  d2 = &bPlayfield[cPrevPlayFieldBit];

  /*printf("[PREV] \tprevPlayFieldBit: %03i, cPrevPlayFieldBit: %03i, cPrevRow: %02i\n",
    prevPlayFieldBit, cPrevPlayFieldBit, cPrevRow);

  printf("[NEXT] \tnextPlayFieldBit: %03i, cNextPlayFieldBit: %03i, cNextRow: %02i\n",
    nextPlayFieldBit, cNextPlayFieldBit, cNextRow);*/

  for (byte x1 = 0; x1 < PLAYFIELD_COLS; x1++) {
    memcpy(d1 + x1, &tileMap[cNextRow][x1], 1);
    memcpy(d2 + x1, &tileMap[cPrevRow][x1], 1);
  }
}
