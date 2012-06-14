/*
 * sortall.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <stdio.h>
#include <peekpoke.h>
#include <6502.h>
#include "memmap.h"
#include "sparta.h"


void sortAll(char* pszDrive, char* pszDirection)
{
	unsigned file_p;
	char* pszFolder = "A:\\*.*";
	struct regs sys_params;

	sparta_init();

	//printf("drive: '%s', sort: '%s'\n", pszDrive, pszDirection);

	//sparta_call("FFIRST")
	file_p = sparta_getVector(SYMBOL_FILE_P);

	//printf("file_p: $%04x: '%s'\n", file_p, *(void**)file_p);

	*(void**)file_p = pszFolder;
	POKE(FATR1, 0x08); // folders only
	POKE(FMODE, 0x0B); // result format

	sparta_call(SYMBOL_FDOPEN);
	sys_params.pc = sparta_getVector(SYMBOL_FDGETC);
	while (_sys(&sys_params), !(sys_params.flags & F6502_N))
	{
		putchar(sys_params.a);
	}
	sparta_call(SYMBOL_FDCLOSE);

	//printf("dirbuf: %s", *(char**)DIRBUF);
}
