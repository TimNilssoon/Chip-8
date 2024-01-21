#ifndef CHIP8_OPCODEHANDLER_H
#define CHIP8_OPCODEHANDLER_H

#include <stdint.h>

// Forward declarations to avoid circular dependencies
typedef struct chip8_core_t *Chip8Core;
const uint16_t *chip8_core_getOpcode(const Chip8Core c);

void chip8_opcodeHandler_execute(Chip8Core c);

#endif