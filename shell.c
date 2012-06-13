/*
 * shell.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <stdlib.h>
#include <string.h>
#include <peekpoke.h>
#include <6502.h>

#include "shell.h"

#define DOSVEC (0x0A)
#define COMTAB ((char*)(PEEKW(DOSVEC)))
#define BUFOFF (COMTAB + 0x0A)
#define LBUF (COMTAB + 0x3F)

//#define FSYMBOL ((0x07EB))

/////////////////////////////////////////////////////////
// public:

FILE* popen(char* pszCommand, char* pszMode)
{
//	char pszXcomliName[] = "XCOMLI  "; // fill spaces to 8 characters
//	unsigned fXcomli = 0;
//	struct regs registers;
//
//	if (pszMode && *pszMode == 'r')
//	{
//		// first, find XCOMLI symbol
//		registers.a = (unsigned)pszXcomliName & 0xFF;
//		registers.x = ((unsigned)pszXcomliName >> 8) & 0xFF;
//		registers.pc = FSYMBOL;
//		_sys(&registers);
//		fXcomli = registers.x * 0x100 + registers.a;
//
//		// clear BUFOFF
//		*BUFOFF = 0;
//
//		// copy command to LBUF, end with new line character
//		strcpy(LBUF, pszCommand);
//		*(LBUF + strlen(pszCommand)) = '\n';
//
//		//  call XCOMLI
//		registers.pc = fXcomli;
//		_sys(&registers);
//	}
//	else
//	{
//		// not supported!
//	}

	return 0;
}
