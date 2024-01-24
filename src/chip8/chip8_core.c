#include "chip8_core.h"
#include "chip8_opcodeHandler.h"
#include "chip8_instructions.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

#define MEM_SIZE 4096
#define V_REGS 16
#define STACK_SIZE 16
#define DISPLAY_BUFFER_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT)
#define KEYS 16

#define FONT_SPRITE_ADDR_OFFSET 0x50
#define ROM_MEM_OFFSET 0x200
#define ROM_MEM_END 0xFFF

#define VREGISTER_X (c->vRegisters[((c->opcode & 0x0F00) >> 8)])
#define VREGISTER_Y (c->vRegisters[((c->opcode & 0x00F0) >> 4)])
#define OPCODE_NNN (c->opcode & 0x0FFF)
#define OPCODE_KK (c->opcode & 0x00FF)
#define OPCODE_N (c->opcode & 0x000F)

struct chip8_core_t {
    uint16_t stack[STACK_SIZE];
    uint16_t displayBuffer[DISPLAY_BUFFER_SIZE];

    uint16_t opcode;
    uint16_t iRegister;
    uint16_t pc;
    
    uint8_t memory[MEM_SIZE];
    uint8_t vRegisters[V_REGS];
    uint8_t keys[KEYS];

    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t sp;
};

static void loadFontSprites(Chip8Core c);

Chip8Core chip8_core_create(void)
{
    Chip8Core c = calloc(1, sizeof(struct chip8_core_t));
    if (c == NULL)
        return NULL;

    return c;
}

void chip8_core_destroy(Chip8Core c)
{
    free(c);
}

void chip8_core_initialize(Chip8Core c)
{
    // Start program execution at ROM address
    c->pc = ROM_MEM_OFFSET;

    loadFontSprites(c);
}

void chip8_core_cycle(Chip8Core c)
{
    // Fetch opcode
    // Bitwise OR together byte at program counter and byte at program counter + 1 to form the opcode
    c->opcode = (c->memory[c->pc] << 8) | c->memory[c->pc + 1];

    // Increment program counter with 2 since an opcode occupies two bytes
    c->pc += 2;

    // Decode and execute opcode
    chip8_opcodeHandler_execute(c);

    // Update timers
}

size_t chip8_core_loadRom(Chip8Core c, const char *filePath)
{
    FILE *fp = fopen(filePath, "rb");
    if (fp == NULL) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    
    // Determine file size
    fseek(fp, 0, SEEK_END);
    size_t fileSize = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);

    const size_t maxFileSize = ROM_MEM_END - ROM_MEM_OFFSET;

    if (fileSize > maxFileSize) {
        fprintf(stderr, "Could not load file: file is too large! Attempted to load %zu bytes. Maximum file size is %zu\n", fileSize, maxFileSize);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    uint8_t *buffer = malloc(fileSize);
    if (buffer == NULL) {
        perror("Error allocating buffer");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(buffer, 1, fileSize, fp);
    fclose(fp);

    memcpy(c->memory + ROM_MEM_OFFSET, buffer, bytesRead);
    free(buffer);

    return bytesRead;
}

static void loadFontSprites(Chip8Core c)
{
    const uint8_t fontSprites[] = { 
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

    memcpy(c->memory + FONT_SPRITE_ADDR_OFFSET, fontSprites, sizeof(fontSprites));
}

const uint16_t *chip8_core_getDisplayBuffer(const Chip8Core c)
{
    return c->displayBuffer;
}

const uint16_t *chip8_core_getOpcode(const Chip8Core c)
{
    return &c->opcode;
}

void chip8_instructions_CLS(Chip8Core c)
{
    memset(c->displayBuffer, 0, sizeof(c->displayBuffer));
}

void chip8_instructions_RET(Chip8Core c)
{
    c->sp--;
    c->pc = c->stack[c->sp];
    c->stack[c->sp] = 0x0;
}

void chip8_instructions_JPNNN(Chip8Core c)
{
    c->pc = OPCODE_NNN;
}

void chip8_instructions_CALLNNN(Chip8Core c)
{
    c->stack[c->sp] = c->pc;
    c->sp++;
    c->pc = OPCODE_NNN;
}

void chip8_instructions_SEVXKK(Chip8Core c)
{
    if (VREGISTER_X == OPCODE_KK)
        c->pc += 2;
}

void chip8_instructions_SNEVXKK(Chip8Core c)
{
    if (VREGISTER_X != OPCODE_KK)
        c->pc += 2;
}

void chip8_instructions_SEVXVY(Chip8Core c)
{
    if (VREGISTER_X != VREGISTER_Y)
        c->pc += 2;  
}

void chip8_instructions_LDVXKK(Chip8Core c)
{
    VREGISTER_X = OPCODE_KK;
}

void chip8_instructions_ADDVXKK(Chip8Core c)
{
    VREGISTER_X += OPCODE_KK;
}

void chip8_instructions_LDVXVY(Chip8Core c)
{
    VREGISTER_X = VREGISTER_Y;
}

void chip8_instructions_ORVXVY(Chip8Core c)
{
    VREGISTER_X |= VREGISTER_Y;
}

void chip8_instructions_ANDVXVY(Chip8Core c)
{
    VREGISTER_X &= VREGISTER_Y;
}

void chip8_instructions_XORVXVY(Chip8Core c)
{
    VREGISTER_X ^= VREGISTER_Y;
}

void chip8_instructions_ADDVXVY(Chip8Core c)
{
    if (VREGISTER_X + VREGISTER_Y > 0xFF)
        c->vRegisters[0xF] = 1;
    else
        c->vRegisters[0xF] = 0;

    VREGISTER_X += VREGISTER_Y;
}

void chip8_instructions_SUBVXVY(Chip8Core c)
{
    if (VREGISTER_X > VREGISTER_Y)
        c->vRegisters[0xF] = 1;
    else
        c->vRegisters[0xF] = 0;

    VREGISTER_X -= VREGISTER_Y;
}

void chip8_instructions_SHRVXVY(Chip8Core c)
{
    c->vRegisters[0xF] = (VREGISTER_X & 0x1);
    VREGISTER_X >>= 1;
}

void chip8_instructions_SUBNVXVY(Chip8Core c)
{
    if (VREGISTER_Y > VREGISTER_X)
        c->vRegisters[0xF] = 1;
    else
        c->vRegisters[0xF] = 0;

    VREGISTER_X = VREGISTER_Y - VREGISTER_X;
}

void chip8_instructions_SHLVXVY(Chip8Core c)
{
    c->vRegisters[0xF] = (VREGISTER_X & 0x80);
    VREGISTER_X <<= 1;
}

void chip8_instructions_LDINNN(Chip8Core c)
{
    c->iRegister = OPCODE_NNN;
}

void chip8_instructions_SNEVXVY(Chip8Core c)
{
    if (VREGISTER_X != VREGISTER_Y)
	    c->pc += 2;
}

void chip8_instructions_JPV0NNN(Chip8Core c)
{
    c->pc = OPCODE_NNN + c->vRegisters[0];
}

void chip8_instructions_RNDVXKK(Chip8Core c)
{
    srand((unsigned int)time(NULL));
    uint8_t randNum = rand() % 256;

    VREGISTER_X = randNum & OPCODE_KK;
}

void chip8_instructions_SKPVX(Chip8Core c)
{
    if (c->keys[VREGISTER_X] != 0)
	    c->pc += 2;
}

void chip8_instructions_SKNPVX(Chip8Core c)
{
    if (c->keys[VREGISTER_X] == 0)
        c->pc += 2;
}

void chip8_instructions_LDVXDT(Chip8Core c)
{
    VREGISTER_X = c->delayTimer;
}

void chip8_instructions_LDVXK(Chip8Core c)
{
    // Temporarily voiding c for compiler's sake
    (void)c;
    // TODO: Implement instruction
}

void chip8_instructions_LDDTVX(Chip8Core c)
{
    c->delayTimer = VREGISTER_X;
}

void chip8_instructions_LDSTVX(Chip8Core c)
{
    c->soundTimer = VREGISTER_X;
}

void chip8_instructions_ADDIVX(Chip8Core c)
{
    c->iRegister += VREGISTER_X;
}

void chip8_instructions_LDFVX(Chip8Core c)
{
    c->iRegister = FONT_SPRITE_ADDR_OFFSET + 0x5 * VREGISTER_X;
}

void chip8_instructions_LDBVX(Chip8Core c)
{
    // Places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2
    c->memory[c->iRegister] = (uint8_t)VREGISTER_X / 100;
    c->memory[c->iRegister + 0x1] = VREGISTER_X / 10 % 10;
    c->memory[c->iRegister + 0x2] = VREGISTER_X % 10;
}

void chip8_instructions_LDIVX(Chip8Core c)
{
    memcpy(c->memory + c->iRegister, c->vRegisters, VREGISTER_X + 1);
}

void chip8_instructions_LDVXI(Chip8Core c)
{
    memcpy(c->vRegisters, c->memory + c->iRegister, VREGISTER_X + 1);
}

void chip8_instructions_DRWVXVY(Chip8Core c)
{
    // Temporarily voiding c for compiler's sake
    (void)c;
    // TODO: Implement instruction
}