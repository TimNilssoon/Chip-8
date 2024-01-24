#ifndef CHIP8_INSTRUCTIONS_H
#define CHIP8_INSTRUCTIONS_H

#include "chip8_chip8CoreType.h"

void chip8_instructions_CLS(Chip8Core c);
void chip8_instructions_RET(Chip8Core c);
void chip8_instructions_JPNNN(Chip8Core c);
void chip8_instructions_CALLNNN(Chip8Core c);
void chip8_instructions_SEVXKK(Chip8Core c);
void chip8_instructions_SNEVXKK(Chip8Core c);
void chip8_instructions_SEVXVY(Chip8Core c);
void chip8_instructions_LDVXKK(Chip8Core c);
void chip8_instructions_ADDVXKK(Chip8Core c);

void chip8_instructions_LDVXVY(Chip8Core c);
void chip8_instructions_ORVXVY(Chip8Core c);
void chip8_instructions_ANDVXVY(Chip8Core c);
void chip8_instructions_XORVXVY(Chip8Core c);
void chip8_instructions_ADDVXVY(Chip8Core c);
void chip8_instructions_SUBVXVY(Chip8Core c);
void chip8_instructions_SHRVXVY(Chip8Core c);
void chip8_instructions_SUBNVXVY(Chip8Core c);
void chip8_instructions_SHLVXVY(Chip8Core c);

void chip8_instructions_SNEVXVY(Chip8Core c);
void chip8_instructions_LDINNN(Chip8Core c);
void chip8_instructions_JPV0NNN(Chip8Core c);
void chip8_instructions_RNDVXKK(Chip8Core c);
void chip8_instructions_SKPVX(Chip8Core c);
void chip8_instructions_SKNPVX(Chip8Core c);
void chip8_instructions_LDVXDT(Chip8Core c);
void chip8_instructions_LDVXK(Chip8Core c);
void chip8_instructions_LDDTVX(Chip8Core c);
void chip8_instructions_LDSTVX(Chip8Core c);
void chip8_instructions_ADDIVX(Chip8Core c);
void chip8_instructions_LDFVX(Chip8Core c);
void chip8_instructions_LDBVX(Chip8Core c);
void chip8_instructions_LDIVX(Chip8Core c);
void chip8_instructions_LDVXI(Chip8Core c);
void chip8_instructions_DRWVXVY(Chip8Core c);

#endif