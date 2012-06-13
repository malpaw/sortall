/*
 * argscheck.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "argscheck.h"

_Bool checkDrive(char* pszDrive)
{
	int len = strlen(pszDrive);
	if (len == 2) // A:, B: etc.
	{
		if (*pszDrive >= 'A' && *pszDrive <= 'Z'
				&& *++pszDrive == ':')
		{
			return true;
		}
	}
	else if (len == 3) // D1:, D2: etc.
	{
		if (*pszDrive == 'D'
				&& *++pszDrive >= '1' && *pszDrive <= '9'
				&& *++pszDrive == ':')
		{
			return true;
		}
	}

	return false;
}

_Bool checkDirection(char* pszDirection)
{
	int len = strlen(pszDirection);
	if (len == 2) // /T, /N etc.
	{
		if (*pszDirection == '/'
				&& (*++pszDirection == 'N'
					|| *pszDirection == 'T'
					|| *pszDirection == 'S'
					|| *pszDirection == 'D'))
		{
			return true;
		}
	}
	else if (len == 3) // /TX, /NX etc.
	{
		if (*pszDirection == '/'
				&& (*++pszDirection == 'N'
					|| *pszDirection == 'T'
					|| *pszDirection == 'S'
					|| *pszDirection == 'D')
				&& *++pszDirection == 'X')
		{
			return true;
		}
	}

	return false;
}

char checkArgs(char argc, char** argv)
{
	switch (argc)
	{
	case 2:
		if (checkDrive(argv[1]))
		{
			return 0;
		}
		break;
	case 3:
		if (checkDrive(argv[1]) && checkDirection(argv[2]))
		{
			return 0;
		}
		break;
	}
	printf("Sorts disk drive entries recursively.\n");
	printf("(c) 2012 uberFat\n\n");
	printf("usage: SORTALL d: [/NTSDX]\n");
	printf("where: /N - sort by name (default)\n");
	printf("       /T - sort by type\n");
	printf("       /S - sort by size\n");
	printf("       /D - sort by date\n");
	printf("       /X - reverse sort\n\n");
	return -1;
}
