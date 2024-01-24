#include "chip8.h"
#include <stdio.h>

static void chip8_initialize_core(Chip8 *c);
static void chip8_initialize_sdl2(Chip8 *c);

void chip8_initialize(Chip8 *c)
{
    chip8_initialize_core(c);
    chip8_initialize_sdl2(c);
}

// Main program loop
// Calls chip8_core_cycle() and SDL2 functions
void chip8_run(Chip8 *c)
{
    //while (1)
    chip8_core_cycle(c->chipCore);
}

void chip8_destroy(Chip8 *c)
{
    // Clean up chip8_core
    chip8_core_destroy(c->chipCore);

    // Clean up SDL2
}

static void chip8_initialize_core(Chip8 *c)
{
    c->chipCore = chip8_core_create();
    if (c->chipCore == NULL) {
        fprintf(stderr, "Chip8 error: Could not initialize Chip-8 Core");
        exit(EXIT_FAILURE);
    }

    chip8_core_initialize(c->chipCore);
}

static void chip8_initialize_sdl2(Chip8 *c)
{
    // Temporarily voiding c for compiler's sake
    (void)c;
    // TODO: Initialize SDL2
}
