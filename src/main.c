#include <stdio.h>
#include "chip8.h"

int main(void)
{
    chip8_initialize();
    chip8_run();

    chip8_quit();
    return 0;
}