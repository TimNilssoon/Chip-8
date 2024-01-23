#include "chip8.h"

int main(void)
{
    Chip8 chip8;
    chip8_initialize(&chip8);
    chip8_run(&chip8);

    chip8_destroy(&chip8);
    return 0;
}