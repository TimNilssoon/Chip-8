#ifndef CHIP8_H
#define CHIP8_H
#include <stdlib.h>

// Chip8 is an ADT of a chip8_t struct pointer
typedef struct chip8_t *Chip8;

Chip8 chip8_create(void);
void chip8_delete(Chip8 c);
void chip8_initialize(Chip8 c);
//void chip8_load_rom(Chip8 c, const char *path);

#endif