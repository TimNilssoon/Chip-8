#ifndef CHIP8_CORE_OPCODEFUNC_H
#define CHIP8_CORE_OPCODEFUNC_H

#include <stdint.h>

typedef struct chip8_core_t *Chip8Core;

const uint16_t *chip8_core_getOpcode(const Chip8Core c);

void chip8_core_CLS(Chip8Core c);
void chip8_core_RET(Chip8Core c);
void chip8_core_JPNNN(Chip8Core c);
void chip8_core_CALLNNN(Chip8Core c);
void chip8_core_SEVXKK(Chip8Core c);
void chip8_core_SNEVXKK(Chip8Core c);
void chip8_core_SEVXVY(Chip8Core c);
void chip8_core_LDVXKK(Chip8Core c);
void chip8_core_ADDVXKK(Chip8Core c);
void chip8_core_LDINNN(Chip8Core c);
void chip8_core_SNEVXVY(Chip8Core c);
void chip8_core_JPV0NNN(Chip8Core c);
void chip8_core_RNDVXKK(Chip8Core c);
void chip8_core_SKPVX(Chip8Core c);
void chip8_core_SKNPVX(Chip8Core c);
void chip8_core(Chip8Core c);

#endif