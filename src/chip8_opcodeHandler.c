#include "chip8_opcodeHandler.h"

typedef void (*OpcodeHandlerFunc)(Chip8Core c);

static void opcode0x0000(Chip8Core c);
static void opcode0x1000(Chip8Core c);
static void opcode0x2000(Chip8Core c);
static void opcode0x3000(Chip8Core c);
static void opcode0x4000(Chip8Core c);
static void opcode0x5000(Chip8Core c);
static void opcode0x6000(Chip8Core c);
static void opcode0x7000(Chip8Core c);
static void opcode0x8000(Chip8Core c);
static void opcode0x9000(Chip8Core c);
static void opcode0xA000(Chip8Core c);
static void opcode0xB000(Chip8Core c);
static void opcode0xC000(Chip8Core c);
static void opcode0xD000(Chip8Core c);
static void opcode0xE000(Chip8Core c);
static void opcode0xF000(Chip8Core c);

OpcodeHandlerFunc opcodeHandlers[16] = {
    opcode0x0000,
    opcode0x1000,
    opcode0x2000,
    opcode0x3000,
    opcode0x4000,
    opcode0x5000,
    opcode0x6000,
    opcode0x7000,
    opcode0x8000,
    opcode0x9000,
    opcode0xA000,
    opcode0xB000,
    opcode0xC000,
    opcode0xD000,
    opcode0xE000,
    opcode0xF000
};


void chip8_opcodeHandler_execute(Chip8Core c)
{
    const uint16_t *opcode = chip8_core_getOpcode(c);

    // Handle opcode
    const uint16_t opcodeIndex = *opcode >> 12;
    opcodeHandlers[opcodeIndex](c);
}

static void opcode0x0000(Chip8Core c)
{
}

static void opcode0x1000(Chip8Core c)
{
}

static void opcode0x2000(Chip8Core c)
{
}

static void opcode0x3000(Chip8Core c)
{
}

static void opcode0x4000(Chip8Core c)
{
}

static void opcode0x5000(Chip8Core c)
{
}

static void opcode0x6000(Chip8Core c)
{
}

static void opcode0x7000(Chip8Core c)
{
}

static void opcode0x8000(Chip8Core c)
{
}

static void opcode0x9000(Chip8Core c)
{
}

static void opcode0xA000(Chip8Core c)
{
}

static void opcode0xB000(Chip8Core c)
{
}

static void opcode0xC000(Chip8Core c)
{
}

static void opcode0xD000(Chip8Core c)
{
}

static void opcode0xE000(Chip8Core c)
{
}

static void opcode0xF000(Chip8Core c)
{
}
