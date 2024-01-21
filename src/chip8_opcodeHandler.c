#include "chip8_opcodeHandler.h"

void chip8_opcodeHandler_execute(Chip8Core c)
{
    const uint16_t *opcode = chip8_core_getOpcode(c);
    
    // Handle opcode
}
