/*
 * shell.c
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#include <string.h>

#include "sparta.h"
#include "shell.h"

/////////////////////////////////////////////////////////
// public:

FILE* popen(char* pszCommand, char* pszMode)
{
	if (pszMode && *pszMode == 'r')
	{
		// clear BUFOFF
		*BUFOFF = 0;

		// copy command to LBUF, end with new line character
		strcpy(LBUF, pszCommand);
		strcat(LBUF, "\n");

		//  call XCOMLI
		sparta_call(SYMBOL_XCOMLI);
	}
	else
	{
		// not supported!
	}

	return 0;
}
