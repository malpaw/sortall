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
//char pszSymbolName[9];

// private:

//char* setName(char* pszName)
//{
//	char* psn = pszSymbolName;
//	int i = 8;
//
//	while (*psn++ = *pszName++)
//	{
//		--i;
//	}
//	--psn; // go one character back to clear terminating zero
//	while (i--)
//	{
//		*psn++ = ' '; // fill with spaces
//	}
//	*psn = 0; // set zero after 8 characters
//
//	return pszSymbolName;
//}

// public:

/**
 * Finds XCOMLI symbol
 */
void sparta_init()
{
	sparta_fXcomli = sparta_getVector(SYMBOL_XCOMLI);
}

unsigned sparta_getVector(char* pszName)
{
	//setName(pszName); // fill spaces to 8 characters
//	sparta_sys_params.a = (unsigned)pszSymbolName & 0xFF;
//	sparta_sys_params.x = ((unsigned)pszSymbolName >> 8) & 0xFF;
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

