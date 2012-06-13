/*
 * sparta.h
 *
 *  Created on: 13-06-2012
 *      Author: albeert
 */

#ifndef SPARTA_H_
#define SPARTA_H_

#define SYMBOL_XCOMLI    ("XCOMLI  ")
#define SYMBOL_FILE_P    ("FILE_P  ")
#define SYMBOL_FFIRST    ("FFIRST  ")
#define SYMBOL_FNEXT     ("FNEXT   ")
#define SYMBOL_FDOPEN    ("FDOPEN  ")
#define SYMBOL_FDGETC    ("FDGETC  ")
#define SYMBOL_FDCLOSE   ("FDCLOSE ")

#define FMODE   (0x0778)
#define FATR1   (0x0779)
#define DIRBUF  (0x0789)

void sparta_init();
unsigned sparta_getVector(char* pszName);
void sparta_call(char* pszName);

#endif /* SPARTA_H_ */
