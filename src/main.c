#include "chip8/chip8.h"

int main(void)
{
    const char *filePath = "";
    Chip8 chip8;
    chip8_initialize(&chip8);
    chip8_loadRom(&chip8, filePath);
    chip8_run(&chip8);

    chip8_destroy(&chip8);
    return 0;
}