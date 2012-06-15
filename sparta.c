/*
 * sparta.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <6502.h>

#include "sparta.h"

#include <stdio.h>

#define FSYMBOL (0x07EB)

union Word
{
	unsigned word;
	struct
	{
		unsigned char lo;
		unsigned char hi;
	} bytes;
};

struct regs sparta_sys_params;
unsigned sparta_fXcomli = 0;

/**
 * Finds XCOMLI symbol
 */
void sparta_init()
{
	sparta_fXcomli = sparta_getVector(SYMBOL_XCOMLI);
}

unsigned sparta_getVector(char* pszName)
{
	sparta_sys_params.a = ((union Word)pszName).bytes.lo;
	sparta_sys_params.x = ((union Word)pszName).bytes.hi;
	sparta_sys_params.pc = FSYMBOL;
	_sys(&sparta_sys_params);
	return ((union Word)sparta_sys_params).word; // note: ensure regs struct begins just like Words union.
}

struct regs* sparta_call(char* pszName)
{
	sparta_sys_params.pc = sparta_getVector(pszName);
	_sys(&sparta_sys_params);
	return &sparta_sys_params;
}

