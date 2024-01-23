#ifndef CHIP8_H
#define CHIP8_H

#include "chip8_core.h"

typedef struct {
    Chip8Core chipCore;
} Chip8;

void chip8_initialize(Chip8 *c);
void chip8_run(Chip8 *c);
void chip8_destroy(Chip8 *c);

#endif