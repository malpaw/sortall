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
#include "sparta.h"
#include "dirinfo.h"
#include "shell.h"

#define new(s) ((struct s*) malloc(sizeof(struct s)))

char pszCommand[COMMANDLINE_LIMIT];

// private:

//void printIndent(int i)
//{
//	while (i--)
//	{
//		putchar(' ');
//	}
//}
//
//void printDirInfo(struct DirInfo* pDirInfo, int indent)
//{
//	while (pDirInfo)
//	{
//		printIndent(indent);
//		printf("%s\n", pDirInfo->pszName);
//		pDirInfo = pDirInfo->pNextEntry;
//	}
//}
//
//
//void printDirTree(char* pszRoot, int indent)
//{
//	struct DirInfo* pDirInfo;
//	struct DirInfo* pDirEntry;
//	char* pszPath = malloc(COMMANDLINE_LIMIT);
//	strcpy(pszPath, pszRoot);
//	strcat(pszPath, "\\*.*");
//
//	pDirEntry = pDirInfo = getDirInfo(pszPath);
//	while (pDirEntry)
//	{
//		printIndent(indent);
//		printf("%s (%s)\n", pDirEntry->pszName, pszRoot);
//
//		strcpy(pszPath, pszRoot);
//		strcat(pszPath, "\\");
//		strcat(pszPath, pDirEntry->pszName);
//		printDirTree(pszPath, indent + 2);
//		pDirEntry = pDirEntry->pNextEntry;
//	}
//
//	deleteDirInfo(pDirInfo);
//	free(pszPath);
//}


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
	struct DirInfo* pFirstEntry = 0;
	struct DirInfo* pDirInfo = 0;
	struct DirInfo* pPrevEntry = 0;

	vFolderName = sparta_getVector(SYMBOL_FILE_P);

	*(void**)vFolderName = pszFolder;
	POKE(FATR1, 0x08); // folders only

	pRegs = sparta_call(SYMBOL_FFIRST);
	while (!(pRegs->flags & F6502_N))
	{
		pDirInfo = new(DirInfo);
		pDirInfo->pNextEntry = 0;
		if (pPrevEntry)
		{
			pPrevEntry->pNextEntry = pDirInfo;
		}
		if (!pFirstEntry)
		{
			pFirstEntry = pDirInfo;
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

	return pFirstEntry;
}

void sortDir(char* pszPath, void* pParam)
{
	strcpy(pszCommand, "ECHO ");
	strcat(pszCommand, pszPath);
	strcat(pszCommand, " ");
	strcat(pszCommand, (void*)pParam);

	//printf("'%s'\n", pszCommand);
	popen(pszCommand, "r");
}

void processDirTree(char* pszRoot, void(*fCallback)(char*, void*), void* pParam)
{
	struct DirInfo* pDirInfo;
	struct DirInfo* pDirEntry;
	char* pszPath = malloc(COMMANDLINE_LIMIT);
	strcpy(pszPath, pszRoot);
	strcat(pszPath, "\\*.*");

	pDirEntry = pDirInfo = getDirInfo(pszPath);
	while (pDirEntry)
	{
		strcpy(pszPath, pszRoot);
		strcat(pszPath, "\\");
		strcat(pszPath, pDirEntry->pszName);
		fCallback(pszPath, pParam);                     // *******
		processDirTree(pszPath, fCallback, pParam);
		pDirEntry = pDirEntry->pNextEntry;
	}

	deleteDirInfo(pDirInfo);
	free(pszPath);
}

// public:

void sortAll(char* pszDrive, char* pszDirection)
{
	sparta_init();
	processDirTree(pszDrive, sortDir, pszDirection);
}
