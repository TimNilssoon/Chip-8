#ifndef CHIP8_CORE_H
#define CHIP8_CORE_H

#include <stdint.h>

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

// Chip8Core is an ADT of a chip8_core_t struct pointer
typedef struct chip8_core_t *Chip8Core;

Chip8Core chip8_core_create(void);
void chip8_core_destroy(Chip8Core c);
void chip8_core_initialize(Chip8Core c);
void chip8_core_cycle(Chip8Core c);
//void chip8_load_rom(Chip8 c, const char *path);

// Returns const pointer to the display buffer
const uint16_t *chip8_core_getDisplayBuffer(const Chip8Core c);

#endif