#include "chip8.h"
#include "chip8_core.h"
#include <stdlib.h>

#define RESOLUTION_SCALE_BY 15

static void chip8_initialize_core(Chip8 *c);
static void chip8_initialize_sdl2(Chip8 *c);

void chip8_initialize(Chip8 *c)
{
    chip8_initialize_core(c);
    chip8_initialize_sdl2(c);

    c->running = true;
}

// Main program loop
// Calls chip8_core_cycle() and SDL2 functions
void chip8_run(Chip8 *c)
{
    while (c->running)
        chip8_core_cycle(c->chipCore);
}

void chip8_destroy(Chip8 *c)
{
    // Clean up chip8_core
    chip8_core_destroy(c->chipCore);

    // Clean up SDL2
    SDL_DestroyRenderer(c->renderer);
    SDL_DestroyWindow(c->window);
    SDL_Quit();
}

size_t chip8_loadRom(Chip8 *c, const char *filePath)
{
    return chip8_core_loadRom(c->chipCore, filePath);
}

// Initialize chip8_core
static void chip8_initialize_core(Chip8 *c)
{
    c->chipCore = chip8_core_create();
    if (c->chipCore == NULL) {
        fprintf(stderr, "Chip8 error: Could not initialize Chip-8 Core");
        exit(EXIT_FAILURE);
    }

    chip8_core_initialize(c->chipCore);
}

// Initialize SDL2
static void chip8_initialize_sdl2(Chip8 *c)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(EXIT_SUCCESS);
    }

    c->window = SDL_CreateWindow("CHIP-8",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                DISPLAY_WIDTH * RESOLUTION_SCALE_BY,
                                DISPLAY_HEIGHT * RESOLUTION_SCALE_BY, 0);
    if (c->window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(EXIT_SUCCESS);
    }

    c->renderer = SDL_CreateRenderer(c->window, -1, SDL_RENDERER_ACCELERATED);
    if (c->renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    }
}
