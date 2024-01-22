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
            chip8_core_CLS(c);
            break;
        
        case 0x00EE: // 0x00EE RET - Return from subroutine
            chip8_core_RET(c);
            break;
    }
}

//0x1NNN JP addr - Jump to address NNN
static void opcode0x1000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_JPNNN(c);
}

// 0x2NNN CALL addr - Call subroutine at address NNN
static void opcode0x2000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_CALLNNN(c);
}

// 0x3XKK SE VX, byte - Skip next instruction if VX == KK
static void opcode0x3000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_SEVXKK(c);
}

// 0x4XKK SNE VX, byte - Skip next instruction if VX != KK
static void opcode0x4000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_SNEVXKK(c);
}

// 0x5XY0 SE VX, VY - Skip next instruction if VX = VY
static void opcode0x5000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_SEVXVY(c);
}

// 0x6XKK LD VX, byte - Set VX = KK
static void opcode0x6000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_LDVXKK(c);
}

// 0x7XKK ADD VX, byte - Set VX = VX + KK
static void opcode0x7000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_ADDVXKK(c);
}

static void opcode0x8000(Chip8Core c, const uint16_t *opcode)
{
}

// 0x9XY0 SNE VX, VY - Skip next instruction if VX != VY
static void opcode0x9000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_SNEVXVY(c);
}

// 0xANNN LD I, addr - Set I = NNN;
static void opcode0xA000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_LDINNN(c);
}

// 0xBNNN JP V0, addr - Jump to address NNN + V0
static void opcode0xB000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_JPV0NNN(c);
}

// 0xCXKK RND VX, byte - Set VX = random byte AND KK
static void opcode0xC000(Chip8Core c, const uint16_t *opcode)
{
    (void)opcode;
    chip8_core_RNDVXKK(c);
}

static void opcode0xD000(Chip8Core c, const uint16_t *opcode)
{
}

static void opcode0xE000(Chip8Core c, const uint16_t *opcode)
{
    switch (*opcode & 0x00FF) {
        case 0x009E: // 0xEX9E SKP VX, Skip next instruction if key with the value of VX is pressed
            chip8_core_SKPVX(c);
            break;
        
        case 0x00A1: // 0xEXA1 SKNP VX, Skip next instruction if key with the value of VX is not pressed
            chip8_core_SKNPVX(c);
            break;
    }
}

static void opcode0xF000(Chip8Core c, const uint16_t *opcode)
{
}
