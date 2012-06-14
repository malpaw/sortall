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
	sparta_sys_params.a = (unsigned)pszName & 0xFF;
	sparta_sys_params.x = ((unsigned)pszName >> 8) & 0xFF;
	sparta_sys_params.pc = FSYMBOL;
	_sys(&sparta_sys_params);
	return sparta_sys_params.x * 0x100 + sparta_sys_params.a;
}

struct regs* sparta_call(char* pszName)
{
	sparta_sys_params.pc = sparta_getVector(pszName);
	_sys(&sparta_sys_params);
	return &sparta_sys_params;
}

