/*
 * sortall.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <peekpoke.h>
#include <6502.h>
#include "memmap.h"
#include "sparta.h"
#include "dirinfo.h"

#define new(s) ((struct s*) malloc(sizeof(struct s)))

struct DirInfo* getDirInfo(char* pszRoot)
{
	unsigned file_p;
	char* pszFolder = strcat(pszRoot, "\\*.*");
	struct regs* pRegs;
	char* pcRead;
	char* pcWrite;
	struct DirInfo* dirInfo;
	struct DirEntry* dirEntry = 0;
	struct DirEntry* dirPrevEntry = 0;

	file_p = sparta_getVector(SYMBOL_FILE_P);

	*(void**)file_p = pszFolder;
	POKE(FATR1, 0x08); // folders only

	dirInfo = new(DirInfo);
	strcpy(dirInfo->pszRoot, pszFolder);
	dirPrevEntry = dirInfo->pEntry;

	pRegs = sparta_call(SYMBOL_FFIRST);
	while (!(pRegs->flags & F6502_N))
	{
		dirEntry = new(DirEntry);
		dirEntry->pNextEntry = 0;
		dirPrevEntry = dirEntry;
		pcWrite = dirEntry->pszName;
		pcRead = (char*)DIRBUF + 6; // name
		while (*pcRead != ' ')
		{
			*pcWrite++ = (*pcRead++);
		}
		// now the extension
		pcRead = (char*)DIRBUF + 14; // ext
		if (*pcRead != ' ')
		{
			*pcWrite++ = '.';
			*pcWrite++ = *pcRead;
			if (*++pcRead != ' ')
			{
				*pcWrite++ = *pcRead;
				if (*++pcRead != ' ')
				{
					*pcWrite++ = *pcRead;
				}
			}
		}
		*pcWrite = 0; // terminate name

		sparta_call(SYMBOL_FNEXT);
	}
	sparta_call(SYMBOL_FCLOSE);

	return dirInfo;
}

void sortAll(char* pszDrive, char* pszDirection)
{
	sparta_init();

	getDirInfo("A:\\TMP");
}
