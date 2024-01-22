#include "chip8_opcodeHandler.h"

typedef void (*OpcodeHandlerFunc)(Chip8Core c, const uint16_t *opcode);

static void opcode0x0000(Chip8Core c, const uint16_t *opcode);
static void opcode0x1000(Chip8Core c, const uint16_t *opcode);
static void opcode0x2000(Chip8Core c, const uint16_t *opcode);
static void opcode0x3000(Chip8Core c, const uint16_t *opcode);
static void opcode0x4000(Chip8Core c, const uint16_t *opcode);
static void opcode0x5000(Chip8Core c, const uint16_t *opcode);
static void opcode0x6000(Chip8Core c, const uint16_t *opcode);
static void opcode0x7000(Chip8Core c, const uint16_t *opcode);
static void opcode0x8000(Chip8Core c, const uint16_t *opcode);
static void opcode0x9000(Chip8Core c, const uint16_t *opcode);
static void opcode0xA000(Chip8Core c, const uint16_t *opcode);
static void opcode0xB000(Chip8Core c, const uint16_t *opcode);
static void opcode0xC000(Chip8Core c, const uint16_t *opcode);
static void opcode0xD000(Chip8Core c, const uint16_t *opcode);
static void opcode0xE000(Chip8Core c, const uint16_t *opcode);
static void opcode0xF000(Chip8Core c, const uint16_t *opcode);

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

    // Extracts the most significant nibble from opcode and uses it as index to get the correct function pointer
    const uint16_t opcodeIndex = *opcode >> 12;
    opcodeHandlers[opcodeIndex](c, opcode);
}

static void opcode0x0000(Chip8Core c, const uint16_t *opcode)
{
    switch (*opcode & 0x00FF) {
        case 0x00E0: // 0x00E0 CLS - Clear display
            chip8_core_clearDisplayBuffer(c);
            break;
        
        case 0x00EE: // 0x00EE RET - Return from subroutine
            chip8_core_returnFromSubroutine(c);
            break;
    }
}

//0x1NNN JP addr - Jump to address NNN
static void opcode0x1000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_jumpToAddress(c);
}

static void opcode0x2000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0x3000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0x4000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0x5000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0x6000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0x7000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0x8000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0x9000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0xA000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0xB000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0xC000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0xD000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0xE000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0xF000(Chip8Core c, const uint16_t *opcode)
{
}
