#ifndef CHIP8_CORE_H
#define CHIP8_CORE_H

#include <stdint.h>
#include <stdlib.h>
#include "chip8Chip8CoreType.h"

#define DISPLAY_WIDTH   64
#define DISPLAY_HEIGHT  32

const uint16_t *chip8Core_getDisplayBuffer(const Chip8Core c);
void chip8Core_setKey(Chip8Core c, uint8_t key);
void chip8Core_resetKeys(Chip8Core c);

Chip8Core chip8Core_create(void);
void chip8Core_destroy(Chip8Core c);
void chip8Core_initialize(Chip8Core c);
void chip8Core_cycle(Chip8Core c);
size_t chip8Core_loadRom(Chip8Core c, const char *filePath);

#endif