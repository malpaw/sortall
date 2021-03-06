/*
 * program.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <stdio.h>
#include <peekpoke.h>
#include "memmap.h"
#include "argscheck.h"
#include "sortall.h"

char main(char argc, char** argv)
{
	char* pDirection;

	POKE(LMARGN, 0x02); // set LMARGN=2
	putchar('\n');

	if (!checkArgs(argc, argv))
	{
		return -1;
	}

	// arguments checked, carry on
	pDirection = (argc == 2) ? "/N" : argv[2];
	sortAll(argv[1], pDirection);
}
