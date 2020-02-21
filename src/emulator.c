#include "../lib/conio/conio.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "screenParams.h"
#include "Types.h"


// CONSTS
// ------------------------------------------------------------------
const char *BLANK = "-";
const char *FILL = "0";


// DEMO ROUTINES
// ------------------------------------------------------------------
void emulatorPrintEngineData(int iScrollX, int iScrollY, byte bXOff, byte bYOff, int ty) {
  printf("TILING MAP DEMO:\n-----------------------------------------------------\n\n");
  printf("PLAYFIELD_ROWS:\t\t%3i\t\tTILEMAP_HEIGHT:\t\t %i\n", PLAYFIELD_ROWS, TILEMAP_HEIGHT);
  printf("PLAYFIELD_COLS:\t\t%3i\t\tTILEMAP_WIDTH:\t\t %i\n\n", PLAYFIELD_COLS, TILEMAP_WIDTH);

  printf("SCREEN_HEIGHT:\t\t%3i\t\tVIEWPORT_HEIGHT:\t%3i\n", SCREEN_HEIGHT, VIEWPORT_HEIGHT);
  printf("SCREEN_WIDTH:\t\t%3i\t\tVIEWPORT_WIDTH:\t\t%3i\n\n", SCREEN_WIDTH, VIEWPORT_WIDTH);

  printf("iScrollX:\t\t%3i\t\tbXOff:\t\t\t%3i\t\t\tty: \t%3i\n",
         iScrollX, bXOff, (ty >= PLAYFIELD_COLS ? ty - PLAYFIELD_COLS : ty));
  printf("iScrollY:\t\t%3i\t\tbYOff:\t\t\t%3i\n", iScrollY, bYOff);

  printf("\n%s\n", bYOff ? "bYOff Mode (step between block complete)" : "NON bYOff (Scroll block completed)");
  printf("\n\nSCREEN REPRESENTATION:\n----------------------\n\n");
}

void emulatorPrintRow(byte data[], int dataLength, byte y) {
  byte i;
  printf("\n[%i]\t ", y);

  for (i = 0; i < dataLength; i += MODULE ) {
    printf("%s", data[i] == 255 ? FILL : BLANK);
  }
}

void emulatorPrintPlayFieldRow(byte row, byte bPlayfield[]) {
  int i,
      dataLength = PLAYFIELD_COLS * PLAYFIELD_ROWS,
      iStart = row * PLAYFIELD_COLS,
      iStop = iStart + PLAYFIELD_COLS,
      color = 1;

  //printf("iStart: %i, iStop: %i\n", iStart, iStop);
  c_textcolor(7);
  printf("[%i]\t [", row);

  for (i = iStart; i < iStop; i++ ) {
    if (bPlayfield[i] == 1) {
      c_textcolor(color);
      printf("%s", FILL);
    } else {
      c_textcolor(11);
      printf("%s", BLANK);
    }

    color = (color > 10) ? 1 : color + 1;

    //printf("%s", bPlayfield[i] == 1 ? FILL : BLANK);
  }

  c_textcolor(7);
  printf("]\n");
}

void emulatorPrintPlayField(byte bPlayfield[]) {
  byte i;

  printf("\n\n\n");
  printf("PLAYFIELD VISUALIZATION (%i bytes):\n------------------------------------\n\n",
         PLAYFIELD_COLS * PLAYFIELD_ROWS);

  for (i = 0; i < PLAYFIELD_ROWS; i++) {
    emulatorPrintPlayFieldRow(i, bPlayfield);
  }

  printf("\n\n");
}

void emulatorPrintDemoMessage() {
  c_textcolor(11); // Light cyan color :)
  c_setcursortype(0);

  printf("======================================================================\n");
  printf("# Press the arrow keys to scroll the screen                          #\n");
  printf("======================================================================");
  c_textcolor(15); // White
}

void cls() {
  system("cls");
}
