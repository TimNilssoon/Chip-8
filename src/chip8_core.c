#include "chip8_core.h"
#include "chip8_opcodeHandler.h"
#include <stdio.h>
#include <string.h>
#include "chip8_core_opcodefuncs.h"

#define MEM_SIZE 4096
#define V_REGS 16
#define STACK_SIZE 16
#define DISPLAY_BUFFER_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT)
#define KEYS 16

#define FONT_SPRITE_OFFSET 0x50
#define ROM_MEM_OFFSET 0x200
#define ROM_MEM_END 0xFFF

#define VREGISTER_X c->vRegisters[((opcode & 0x0F00) >> 8)]
#define VREGISTER_Y c->vRegisters[((opcode & 0x00F0) >> 4)]
#define OPCODE_NNN c->opcode & 0x0FFF
#define OPCODE_KK c->opcode & 0x00FF
#define OPCODE_N c->opcode & 0x000F

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

static void loadFontSprites(struct chip8_core_t *c);

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
    // Start execution at ROM address
    c->pc = ROM_MEM_OFFSET;

    c->memory[0x200] = 0x00;
    c->memory[0x201] = 0xE0;
    c->memory[0x202] = 0x00;
    c->memory[0x203] = 0xEE;

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

size_t chip8_core_loadRom(Chip8Core c, const char *path)
{
    FILE *fp = fopen(path, "rb");
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

const uint16_t *chip8_core_getDisplayBuffer(const Chip8Core c)
{
    return c->displayBuffer;
}

void chip8_core_clearDisplayBuffer(Chip8Core c)
{
    memset(c->displayBuffer, 0, sizeof(c->displayBuffer));
}

void chip8_core_returnFromSubroutine(Chip8Core c)
{
    c->sp--;
    c->pc = c->stack[c->sp];
    c->stack[c->sp] = 0x0;
}

void chip8_core_jumpToAddress(Chip8Core c)
{
    c->pc = OPCODE_NNN;
}

const uint16_t *chip8_core_getOpcode(const Chip8Core c)
{
    return &c->opcode;
}

static void loadFontSprites(struct chip8_core_t *c)
{
    uint8_t fontSprites[] = { 
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

    memcpy(c->memory + FONT_SPRITE_OFFSET, fontSprites, sizeof(fontSprites));
}
