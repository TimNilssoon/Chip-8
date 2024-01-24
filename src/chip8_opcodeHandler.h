#ifndef CHIP8_OPCODEHANDLER_H
#define CHIP8_OPCODEHANDLER_H

#include <stdint.h>
#include "chip8_chip8CoreType.h"

// Forward declaration
const uint16_t *chip8_core_getOpcode(const Chip8Core c);

void chip8_opcodeHandler_execute(Chip8Core c);

#endif