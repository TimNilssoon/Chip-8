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

void chip8_core_LDVXVY(Chip8Core c);
void chip8_core_ORVXVY(Chip8Core c);
void chip8_core_ANDVXVY(Chip8Core c);
void chip8_core_XORVXVY(Chip8Core c);
void chip8_core_ADDVXVY(Chip8Core c);
void chip8_core_SUBVXVY(Chip8Core c);
void chip8_core_SHRVXVY(Chip8Core c);
void chip8_core_SUBNVXVY(Chip8Core c);
void chip8_core_SHLVXVY(Chip8Core c);

void chip8_core_SNEVXVY(Chip8Core c);
void chip8_core_LDINNN(Chip8Core c);
void chip8_core_JPV0NNN(Chip8Core c);
void chip8_core_RNDVXKK(Chip8Core c);
void chip8_core_SKPVX(Chip8Core c);
void chip8_core_SKNPVX(Chip8Core c);
void chip8_core_LDVXDT(Chip8Core c);
void chip8_core_LDVXK(Chip8Core c);
void chip8_core_LDDTVX(Chip8Core c);
void chip8_core_LDSTVX(Chip8Core c);
void chip8_core_ADDIVX(Chip8Core c);
void chip8_core_LDFVX(Chip8Core c);
void chip8_core_LDBVX(Chip8Core c);
void chip8_core_LDIVX(Chip8Core c);
void chip8_core_LDVXI(Chip8Core c);
void chip8_core_DRWVXVY(Chip8Core c);

#endif