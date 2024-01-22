#ifndef CHIP8_CORE_H
#define CHIP8_CORE_H

#include <stdint.h>
#include <stdlib.h>
#include "chip8_core_opcodefuncs.h"

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

Chip8Core chip8_core_create(void);
void chip8_core_destroy(Chip8Core c);
void chip8_core_initialize(Chip8Core c);
void chip8_core_cycle(Chip8Core c);
size_t chip8_core_loadRom(Chip8Core c, const char *path);

#endif