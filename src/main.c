#include <stdio.h>
#include "chip8.h"

int main(void)
{
    Chip8 chip = chip8_create();
    if (chip == NULL) {
        fprintf(stderr, "Chip-8 Error: Could not allocate memory");
        exit(EXIT_FAILURE);
    }
    chip8_initialize(chip);

    chip8_delete(chip);

    exit(EXIT_SUCCESS);
}