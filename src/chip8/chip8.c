#include "chip8.h"
#include "chip8_core.h"
#include <stdlib.h>

#define RESOLUTION_SCALE_BY 15
#define FRAME_RATE 60
#define FRAME_TIME (1000 / FRAME_RATE)

static void chip8_initializeCore(Chip8 *c);
static void chip8_initializeSDL2(Chip8 *c);
static void chip8_renderFrame(Chip8 *c);
static void chip8_handleInput(Chip8 *c);

void chip8_initialize(Chip8 *c)
{
    chip8_initializeCore(c);
    chip8_initializeSDL2(c);

    #if DEBUG
    c->deltaTime = 0.0;
    c->frameStart = 0.0;
    c->frameEnd = 0.0;
    c->frames = 0;
    c->fpsTimer = 0.0f;
    #endif
}

// Main program loop
// Calls chip8_core_cycle() and SDL2 functions
void chip8_run(Chip8 *c)
{
    while (1) {
        #if DEBUG
        c->frameStart = SDL_GetTicks64() / 1000;
        #endif

        // Handle exit event
        SDL_PollEvent(&c->event);
        if (c->event.type == SDL_QUIT)
            return;

        chip8_handleInput(c);
        chip8_core_cycle(c->chipCore);
        chip8_renderFrame(c);

        SDL_Delay(FRAME_TIME);
        
        #if DEBUG
        // Calculate frame rate
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
        #endif
    }
}

void chip8_destroy(Chip8 *c)
{
    // Clean up SDL2
    SDL_DestroyRenderer(c->renderer);
    SDL_DestroyWindow(c->window);
    SDL_Quit();

    // Clean up chip8_core
    chip8_core_destroy(c->chipCore);

    // Lastly free Chip8 struct
    free(c);
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

void chip8_handleInput(Chip8 *c)
{
    if (c->event.type == SDL_KEYDOWN) {
        c->keyboardState = SDL_GetKeyboardState(NULL);

        if (c->keyboardState[SDL_SCANCODE_X]) {
            chip8_core_setKey(c->chipCore, 0x0);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '0'); // 0 = x
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_1]) {
            chip8_core_setKey(c->chipCore, 0x1);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '1'); // 1 = 1
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_2]) {
            chip8_core_setKey(c->chipCore, 0x2);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '2'); // 2 = 2
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_3]) {
            chip8_core_setKey(c->chipCore, 0x3);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '3'); // 3 = 3
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_Q]) {
            chip8_core_setKey(c->chipCore, 0x4);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '4'); // 4 = q
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_W]) {
            chip8_core_setKey(c->chipCore, 0x5);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '5'); // 5 = w
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_E]) {
            chip8_core_setKey(c->chipCore, 0x6);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '6'); // 6 = e
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_A]) {
            chip8_core_setKey(c->chipCore, 0x7);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '7'); // 7 = a
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_S]) {
            chip8_core_setKey(c->chipCore, 0x8);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '8'); // 8 = s
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_D]) {
            chip8_core_setKey(c->chipCore, 0x9);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", '9'); // 9 = d
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_Z]) {
            chip8_core_setKey(c->chipCore, 0xA);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", 'A'); // A = z
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_C]) {
            chip8_core_setKey(c->chipCore, 0xB);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", 'B'); // B = c
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_4]) {
            chip8_core_setKey(c->chipCore, 0xC);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", 'C'); // C = 4
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_R]) {
            chip8_core_setKey(c->chipCore, 0xD);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", 'D'); // D = r
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_F]) {
            chip8_core_setKey(c->chipCore, 0xE);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", 'E'); // E = f
            #endif
        }

        if (c->keyboardState[SDL_SCANCODE_V]) {
            chip8_core_setKey(c->chipCore, 0xF);
            #if DEBUG
            printf("DEBUG: Key pressed: %c\n", 'F'); // F = v
            #endif
        }

    }
    else
        chip8_core_resetKeys(c->chipCore);
}

static void chip8_renderFrame(Chip8 * c)
{
    (void)c;
}

