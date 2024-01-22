#ifndef CHIP8_CORE_OPCODEFUNC_H
#define CHIP8_CORE_OPCODEFUNC_H

#include <stdint.h>

// Chip8Core is an ADT of a chip8_core_t struct pointer
typedef struct chip8_core_t *Chip8Core;

const uint16_t *chip8_core_getDisplayBuffer(const Chip8Core c);

const uint16_t *chip8_core_getOpcode(const Chip8Core c);

void chip8_core_clearDisplayBuffer(Chip8Core c);
void chip8_core_returnFromSubroutine(Chip8Core c);
void chip8_core_jumpToAddress(Chip8Core c);

#endif