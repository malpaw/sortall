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


// private:

void printDirInfo(struct DirInfo* pDirInfo)
{
	while (pDirInfo)
	{
		printf(": %s\n", pDirInfo->pszName);
		pDirInfo = pDirInfo->pNextEntry;
	}
}

void deleteDirInfo(struct DirInfo* pDirInfo)
{
	struct DirInfo* next;

	while (pDirInfo)
	{
		next = pDirInfo->pNextEntry;
		free(pDirInfo);
		pDirInfo = next;
	}
}

struct DirInfo* getDirInfo(char* pszFolder)
{
	unsigned vFolderName;
	struct regs* pRegs;
	char* pcRead;
	char* pcWrite;
	struct DirInfo* pDirInfo;
	struct DirInfo* pPrevEntry = 0;

	vFolderName = sparta_getVector(SYMBOL_FILE_P);

	*(void**)vFolderName = pszFolder;
	POKE(FATR1, 0x08); // folders only

	//pDirInfo = new(DirInfo);
	//strcpy(pDirInfo->pszRoot, pszFolder);
	//pPrevEntry = pDirInfo->pNextEntry;

	pRegs = sparta_call(SYMBOL_FFIRST);
	while (!(pRegs->flags & F6502_N))
	{
		pDirInfo = new(DirInfo);
		pDirInfo->pNextEntry = 0;
		if (pPrevEntry)
		{
			pPrevEntry->pNextEntry = pDirInfo;
		}
		pPrevEntry = pDirInfo;
		pcWrite = pDirInfo->pszName;
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

	return pDirInfo;
}

// public:

void sortAll(char* pszDrive, char* pszDirection)
{
	struct DirInfo* pDirInfo;

	sparta_init();

	pDirInfo = getDirInfo("A:\\TMP\\*.*");

	printDirInfo(pDirInfo);

	deleteDirInfo(pDirInfo);
}
