/*
 * program.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <stdio.h>
#include <peekpoke.h>
#include "sortall.h"

char main(char argc, char** argv)
{
	int retCode;

	POKE(0x0052, 0x02); // set LMARGIN=2
	putchar('\n');

	retCode = checkArgs(argc, argv);
	if (!retCode)
	{
		return retCode;
	}

	// arguments parsed, carry on
}
