/*
 * sortall.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <stdio.h>

char checkArgs(char argc, char** argv)
{
	if (argc == 2 || argc == 3)
	{
		return 0;
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
