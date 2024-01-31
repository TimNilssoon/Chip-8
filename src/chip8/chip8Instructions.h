#ifndef CHIP8_INSTRUCTIONS_H
#define CHIP8_INSTRUCTIONS_H

#include "chip8Chip8CoreType.h"

void chip8Instructions_CLS(Chip8Core c);
void chip8Instructions_RET(Chip8Core c);
void chip8Instructions_JPNNN(Chip8Core c);
void chip8Instructions_CALLNNN(Chip8Core c);
void chip8Instructions_SEVXKK(Chip8Core c);
void chip8Instructions_SNEVXKK(Chip8Core c);
void chip8Instructions_SEVXVY(Chip8Core c);
void chip8Instructions_LDVXKK(Chip8Core c);
void chip8Instructions_ADDVXKK(Chip8Core c);

void chip8Instructions_LDVXVY(Chip8Core c);
void chip8Instructions_ORVXVY(Chip8Core c);
void chip8Instructions_ANDVXVY(Chip8Core c);
void chip8Instructions_XORVXVY(Chip8Core c);
void chip8Instructions_ADDVXVY(Chip8Core c);
void chip8Instructions_SUBVXVY(Chip8Core c);
void chip8Instructions_SHRVXVY(Chip8Core c);
void chip8Instructions_SUBNVXVY(Chip8Core c);
void chip8Instructions_SHLVXVY(Chip8Core c);

void chip8Instructions_SNEVXVY(Chip8Core c);
void chip8Instructions_LDINNN(Chip8Core c);
void chip8Instructions_JPV0NNN(Chip8Core c);
void chip8Instructions_RNDVXKK(Chip8Core c);
void chip8Instructions_SKPVX(Chip8Core c);
void chip8Instructions_SKNPVX(Chip8Core c);
void chip8Instructions_LDVXDT(Chip8Core c);
void chip8Instructions_LDVXK(Chip8Core c);
void chip8Instructions_LDDTVX(Chip8Core c);
void chip8Instructions_LDSTVX(Chip8Core c);
void chip8Instructions_ADDIVX(Chip8Core c);
void chip8Instructions_LDFVX(Chip8Core c);
void chip8Instructions_LDBVX(Chip8Core c);
void chip8Instructions_LDIVX(Chip8Core c);
void chip8Instructions_LDVXI(Chip8Core c);
void chip8Instructions_DRWVXVY(Chip8Core c);

#endif