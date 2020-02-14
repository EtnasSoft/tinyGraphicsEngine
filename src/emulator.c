#include "emulator.h"

// DEMO ROUTINES
// ------------------------------------------------------------------
void PrintRow(byte data[], int dataLength, byte y) {
  byte i;
  printf("\n[%i]\t ", y);

  for (i = 0; i <= dataLength; i += MODULE ) {
    printf("%s", data[i] == 255 ? FILL : BLANK);
  }
}

void PrintPlayFieldRow(byte row) {
  int i,
      dataLength = PLAYFIELD_COLS * PLAYFIELD_ROWS,
      iStart = row * PLAYFIELD_COLS,
      iStop = iStart + PLAYFIELD_COLS,
      color = 1;

  //printf("iStart: %i, iStop: %i\n", iStart, iStop);
  printf("[%i]\t [", row);

  for (i = iStart; i < iStop; i++ ) {
    if (bPlayfield[i] == 1) {
      c_textcolor(color++ & 3);
      printf("%s", FILL);
    } else {
      c_textcolor(11);
      printf("%s", BLANK);
    }
    //printf("%s", bPlayfield[i] == 1 ? FILL : BLANK);
  }

  printf("]\n");
}

void PrintPlayField() {
  byte i;

  printf("PLAYFIELD VISUALIZATION (%i bytes):\n------------------------------------\n\n",
         PLAYFIELD_COLS * PLAYFIELD_ROWS);

  for (i = 0; i < PLAYFIELD_ROWS; i++) {
    PrintPlayFieldRow(i);
  }

  printf("\n\n");
}

void PrintDemoMessage() {
  c_setcursortype(0);

  printf("╔═══════════════════════════════════════════════════════════════════╗\n");
  printf("║ Press the arrow keys to scroll the screen                         ║\n");
  printf("╚═══════════════════════════════════════════════════════════════════╝");
}

void cls() {
  c_clrscr();
}
