#ifndef CHIP8_CORE_H
#define CHIP8_CORE_H

#include <stdint.h>
#include <stdlib.h>

// Chip8Core is an ADT of a chip8_core_t struct pointer
typedef struct chip8_core_t *Chip8Core;

const uint16_t *chip8_core_getDisplayBuffer(const Chip8Core c);

Chip8Core chip8_core_create(void);
void chip8_core_destroy(Chip8Core c);
void chip8_core_initialize(Chip8Core c);
void chip8_core_cycle(Chip8Core c);
size_t chip8_core_loadRom(Chip8Core c, const char *path);

#endif