/*
 * memmap.h
 *
 *  Created on: 14-06-2012
 *      Author: albeert
 */

#ifndef MEMMAP_H_
#define MEMMAP_H_

#define LMARGIN    (0x0052)

// SDX file operation vectors
#define DOSVEC     (0x000A)
#define COMTAB     ((char*)(PEEKW(DOSVEC)))
#define BUFOFF     (COMTAB + 0x0A)
#define LBUF       (COMTAB + 0x03F)
#define FMODE      (0x0778)
#define FATR1      (0x0779)
#define DIRBUF     (0x0789)



#endif /* MEMMAP_H_ */
