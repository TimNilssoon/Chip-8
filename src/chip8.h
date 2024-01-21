#ifndef CHIP8_H
#define CHIP8_H
#include <stdint.h>

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

// Chip8 is an ADT of a chip8_t struct pointer
typedef struct chip8_t *Chip8;

Chip8 chip8_create(void);
void chip8_destroy(Chip8 c);
void chip8_initialize(Chip8 c);
//void chip8_load_rom(Chip8 c, const char *path);

// Returns const pointer to the display buffer
const uint16_t *chip8_get_display_buffer(const Chip8 c);

#endif