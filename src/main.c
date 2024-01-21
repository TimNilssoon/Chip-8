#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

int main(void)
{
    chip8_initialize();
    chip8_run();

    chip8_quit();
    exit(EXIT_SUCCESS);
}