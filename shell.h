/*
 * shell.h
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdbool.h>

void popen(char* command);
void popen_uload(char* command, char* pszOutputFileName);

#endif /* SHELL_H_ */
