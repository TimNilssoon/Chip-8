#ifndef CHIP8_OPCODEHANDLER_H
#define CHIP8_OPCODEHANDLER_H

#include <stdint.h>
#include "chip8Chip8CoreType.h"

// Forward declaration
const uint16_t *chip8Core_getOpcode(const Chip8Core c);

void chip8OpcodeHandler_execute(Chip8Core c);

#endif