#include "chip8/chip8.h"

#define EXPECTED_ARGS 2

int main(int argc, char *argv[])
{
    if (argc != EXPECTED_ARGS) {
        fprintf(stderr, "Usage: %s <path to rom>\n", argv[0]);
        return 1;
    }
    
    Chip8 *chip8 = chip8_create();
    if (chip8 == NULL) {
        fprintf(stderr, "Chip8 error: Could not allocate memory for Chip-8");
        exit(EXIT_FAILURE);
    }
    chip8_initialize(chip8);
    chip8_loadRom(chip8, argv[1]);
    chip8_run(chip8);

    chip8_destroy(chip8);
    return 0;
}
