#include "chip8.h"
#include "chip8_core.h"

static Chip8Core chipCore;

void chip8_initialize(void)
{
    // Create and initialize chip8_core
    chipCore = chip8_core_create();
    chip8_core_initialize(chipCore);

    //  Initialize SDL2
}

// Main program loop
// Calls chip8_core_cycle() and SDL2 functions
void chip8_run(void)
{
    chip8_core_cycle(chipCore);
}

void chip8_quit(void)
{
    // Clean up chip8_core
    chip8_core_destroy(chipCore);

    // Clean up SDL2
}
