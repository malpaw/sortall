/*
 * sparta.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

//#include <6502.h>

//#include "sparta.h"

#define FSYMBOL (0x07EB)

//struct regs sdx_sys_params;
unsigned sparta_fXcomli = 0;
char pszSymbolName[9];

// private:

char* setName(char* pszName)
{
	char* psn = pszSymbolName;
	int i = 8;

	while (*psn++ = *pszName++)
	{
		--i;
	}
	++i; // clear zero
	while (i--)
	{
		*psn++ = ' '; // fill with spaces
	}
	*psn = 0; // set zero after 8 characters
	return pszSymbolName;
}

// public:

/**
 * Finds XCOMLI symbol
 */
void sparta_init()
{
	setName("XCOMLI"); // fill spaces to 8 characters
//	sparta_sys_params.a = (unsigned)pszSymbolName & 0xFF;
//	sparta_sys_params.x = ((unsigned)pszSymbolName >> 8) & 0xFF;
//	sparta_sys_params.pc = FSYMBOL;
//	_sys(&sparta_sys_params);
//	sparta_fXcomli = sparta_sys_params.x * 0x100 + sparta_sys_params.a;
}

unsigned sparta_getattr(char* pszName)
{
	setName(pszName);
	return 0;
}
