/*
 * shell.h
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>

#define COMMANDLINE_LIMIT (63)


FILE* popen(char* command, char* mode);

#endif /* SHELL_H_ */
