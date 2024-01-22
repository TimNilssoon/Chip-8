#include "chip8.h"
#include "chip8_core.h"

static Chip8Core chipCore;

void chip8_initialize(void)
{
    // Create and initialize chip8_core
    chipCore = chip8_core_create();
    if (chipCore == NULL) {
        fprintf(stderr, "Chip8 error: Could not initialize Chip-8 Core");
        exit(EXIT_FAILURE);
    }

    chip8_core_initialize(chipCore);
    //chip8_core_loadRom(chipCore, "/home/ubuntu/repos/chip-8/roms/test_opcode.ch8");

    //  Initialize SDL2
}

// Main program loop
// Calls chip8_core_cycle() and SDL2 functions
void chip8_run(void)
{
    while (1)
        chip8_core_cycle(chipCore);
}

void chip8_quit(void)
{
    // Clean up chip8_core
    chip8_core_destroy(chipCore);

    // Clean up SDL2
}
