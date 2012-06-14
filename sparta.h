/*
 * sparta.h
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#ifndef SPARTA_H_
#define SPARTA_H_

#include <peekpoke.h>
#include "memmap.h"

#define COMMANDLINE_LIMIT (63)

#define SYMBOL_XCOMLI    ("XCOMLI  ")
#define SYMBOL_FILE_P    ("FILE_P  ")
#define SYMBOL_FFIRST    ("FFIRST  ")
#define SYMBOL_FNEXT     ("FNEXT   ")
#define SYMBOL_FCLOSE    ("FCLOSE  ")
#define SYMBOL_FDOPEN    ("FDOPEN  ")
#define SYMBOL_FDGETC    ("FDGETC  ")
#define SYMBOL_FDCLOSE   ("FDCLOSE ")
#define SYMBOL_U_GETPAR  ("U_GETPAR")
#define SYMBOL_U_LOAD    ("U_LOAD  ")
#define SYMBOL_FILE_P    ("FILE_P  ")
#define SYMBOL_DIVIO     ("DIVIO   ")
#define SYMBOL_XDIVIO    ("XDIVIO  ")
#define SYMBOL_PUT_V     ("PUT_V   ")

void sparta_init();
unsigned sparta_getVector(char* pszName);
struct regs* sparta_call(char* pszName);

#endif /* SPARTA_H_ */
