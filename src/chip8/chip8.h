#ifndef CHIP8_H
#define CHIP8_H

#include "chip8_chip8CoreType.h"
#include <stdio.h>
#include <SDL.h>

typedef struct {
    Chip8Core chipCore;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    uint16_t *coreDisplayBuffer;

    // Frame rate data fields
    double deltaTime;
    double frameStart;
    double frameEnd;
    float fpsTimer;
    int frames;
} Chip8;

Chip8 *chip8_create(void);
void chip8_initialize(Chip8 *c);
void chip8_run(Chip8 *c);
void chip8_destroy(Chip8 *c);
size_t chip8_loadRom(Chip8 *c, const char *filePath);

#endif