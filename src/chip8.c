#include "chip8.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MEM_SIZE 4096
#define V_REGS 16
#define STACK_SIZE 16
#define DISPLAY_BUFFER_SIZE  (DISPLAY_WIDTH * DISPLAY_HEIGHT)
#define KEYS 16

#define FONT_SPRITE_OFFSET 0x50

struct chip8_t {
    uint16_t stack[STACK_SIZE];
    uint16_t display_buffer[DISPLAY_BUFFER_SIZE];

    uint16_t opcode;
    uint16_t i_register;
    uint16_t pc;
    
    uint8_t memory[MEM_SIZE];
    uint8_t v_registers[V_REGS];
    uint8_t keys[KEYS];

    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t sp;
};

void load_font_sprites(struct chip8_t *c);

Chip8 chip8_create(void)
{
    Chip8 c = calloc(1, sizeof(struct chip8_t));
    if (c == NULL)
        return NULL;

    return c;
}

void chip8_destroy(Chip8 c)
{
    free(c);
}

void chip8_initialize(Chip8 c)
{
    assert(c != NULL);
    c->pc = 0x200;

    load_font_sprites(c);
}

const uint16_t *chip8_get_display_buffer(const Chip8 c)
{
    return c->display_buffer;
}

void load_font_sprites(struct chip8_t *c)
{
    uint8_t font_sprites[] = { 
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

    memcpy(c->memory + FONT_SPRITE_OFFSET, font_sprites, sizeof(font_sprites));
}
