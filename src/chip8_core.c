#include "chip8_core.h"
#include <stdio.h>
#include <string.h>

#define MEM_SIZE 4096
#define V_REGS 16
#define STACK_SIZE 16
#define DISPLAY_BUFFER_SIZE  (DISPLAY_WIDTH * DISPLAY_HEIGHT)
#define KEYS 16

#define FONT_SPRITE_OFFSET 0x50
#define ROM_MEM_OFFSET 0x200
#define ROM_MEM_END 0xFFF

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

void loadFontSprites(struct chip8_core_t *c);

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

void loadFontSprites(struct chip8_core_t *c)
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
