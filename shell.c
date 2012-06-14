/*
 * shell.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <string.h>
#include <peekpoke.h>
#include <6502.h>

#include "sparta.h"
#include "shell.h"

/////////////////////////////////////////////////////////
// public:

/**
 * Launches SDX command using COMMAND.COM
 * @param pszCommand
 */
void popen(char* pszCommand)
{
	// clear BUFOFF
	POKE(BUFOFF, 0);

	// copy command to LBUF
	strcpy((char*)LBUF, pszCommand);
	strcat((char*)LBUF, "\n");

	//  call XCOMLI
	sparta_call(SYMBOL_XCOMLI);
}

/**
 * Launches SDX command using U_LOAD system call
 * @param pszCommand
 */
void popen_uload(char *pszCommand, char* pszOutputFileName)
{
	struct regs r;
	unsigned fOutputHandle;
	unsigned vFileP;

	// redirect standard output
	if (pszOutputFileName)
	{
		vFileP = sparta_getVector(SYMBOL_FILE_P);
		*(char**)vFileP = pszOutputFileName;
		r.y = 0x00; // redirect standard output;
		r.pc = sparta_getVector(SYMBOL_DIVIO);
		_sys(&r);
		fOutputHandle = PEEKW(FHANDLE);
	}

	// clear BUFOFF
	POKE(BUFOFF, 0);

	// copy command to LBUF
	strcpy((char*)LBUF, pszCommand);
	strcat((char*)LBUF, "\n");

	// call U_GETPAR to fetch command name (mimic COMMAND.COM behavior)
	sparta_call(SYMBOL_U_GETPAR);

	// clear FLAG
	r.flags = 0;

	// call U_LOAD
	r.pc = sparta_getVector(SYMBOL_U_LOAD);
	_sys(&r);
	// TODO: set trap!

	// restore standard output
	if (pszOutputFileName)
	{
		POKEW(FHANDLE, fOutputHandle);
		r.y = 0x00; // restore standard output
		r.pc = sparta_getVector(SYMBOL_XDIVIO);
		_sys(&r);
	}
}


