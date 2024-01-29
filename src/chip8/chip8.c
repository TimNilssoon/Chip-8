#include "chip8.h"
#include "chip8_core.h"
#include <stdlib.h>
#include <unistd.h>

#define RESOLUTION_SCALE_BY 15
#define FRAME_RATE 59
#define FRAME_TIME (1000 / FRAME_RATE)

static void chip8_initializeCore(Chip8 *c);
static void chip8_initializeSDL2(Chip8 *c);
static void chip8_renderFrame(Chip8 *c);

void chip8_initialize(Chip8 *c)
{
    chip8_initializeCore(c);
    chip8_initializeSDL2(c);

    c->deltaTime = 0.0;
    c->frameStart = 0.0;
    c->frameEnd = 0.0;
    c->frames = 0;
    c->fpsTimer = 0.0f;
}

// Main program loop
// Calls chip8_core_cycle() and SDL2 functions
void chip8_run(Chip8 *c)
{
    SDL_Event e;

    while (1) {
        c->frameStart = SDL_GetTicks64() / 1000;
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT || e.type == SDL_KEYUP)
            return;

        chip8_core_cycle(c->chipCore);
        chip8_renderFrame(c);

        SDL_Delay(FRAME_TIME);
        
        c->frameEnd = SDL_GetTicks64() / 1000;
        c->deltaTime = c->frameEnd - c->frameStart;

        c->fpsTimer += c->deltaTime;
        c->frames++;

        if (c->fpsTimer >= 1.0f) {
            float fps = c->frames / c->fpsTimer;
            printf("%.2f\n", fps);

            c->fpsTimer = 0.0f;
            c->frames = 0;
        }
    }
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

Chip8 *chip8_create(void)
{
    Chip8 *chipPtr = malloc(sizeof(Chip8));
    if (chipPtr == NULL)
        return NULL;
    
    return chipPtr;
}

size_t chip8_loadRom(Chip8 *c, const char *filePath)
{
    return chip8_core_loadRom(c->chipCore, filePath);
}

// Initialize chip8_core
static void chip8_initializeCore(Chip8 *c)
{
    c->chipCore = chip8_core_create();
    if (c->chipCore == NULL) {
        fprintf(stderr, "Chip8 error: Could not initialize Chip-8 Core");
        exit(EXIT_FAILURE);
    }

    chip8_core_initialize(c->chipCore);
    c->coreDisplayBuffer = chip8_core_getDisplayBuffer(c->chipCore);
}

// Initialize SDL2
static void chip8_initializeSDL2(Chip8 *c)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    c->window = SDL_CreateWindow("CHIP-8",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                DISPLAY_WIDTH * RESOLUTION_SCALE_BY,
                                DISPLAY_HEIGHT * RESOLUTION_SCALE_BY, 0);
    if (c->window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    c->renderer = SDL_CreateRenderer(c->window, -1, SDL_RENDERER_ACCELERATED);
    if (c->renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    c->texture = SDL_CreateTexture(c->renderer,
                                    SDL_PIXELFORMAT_ARGB1555,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    DISPLAY_WIDTH,
                                    DISPLAY_HEIGHT);
    if (c->texture == NULL) {
        fprintf(stderr, "SDL_CreateTexture Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

static void chip8_renderFrame(Chip8 * c)
{
    (void)c;
}
