#ifndef GRAPHICSENGINECLION_SCREENPARAMS_H
#define GRAPHICSENGINECLION_SCREENPARAMS_H

// Screen resolution 128x64px
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define MODULE 8 // Module for tiles (bits) used for screen division / pages
#define EDGES 2 // Used only for pseudo buffer screen purposes

#define VIEWPORT_WIDTH SCREEN_WIDTH / MODULE
#define VIEWPORT_HEIGHT SCREEN_HEIGHT / MODULE

// MAXIMUM: 16rows x 18cols => 288 byte + 128 byte (SSD1306 page)
#define PLAYFIELD_ROWS (VIEWPORT_HEIGHT + EDGES) // AXIS Y
#define PLAYFIELD_COLS (VIEWPORT_WIDTH + EDGES) // AXIS X

#define TILEMAP_HEIGHT 29
#define TILEMAP_WIDTH PLAYFIELD_COLS

#define SCREEN_SLAVE_ADDRESS 0x3C

#endif // GRAPHICSENGINECLION_SCREENPARAMS_H
