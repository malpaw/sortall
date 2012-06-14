/*
 * dirinfo.h
 *
 *  Created on: 14-06-2012
 *      Author: albeert
 */

#ifndef DIRINFO_H_
#define DIRINFO_H_

struct DirEntry
{
	char pszName[13]; // 8.3+zero
	struct DirEntry* pNextEntry;
};

struct DirInfo
{
	char pszRoot[13]; // 8.3+zero
	struct DirEntry* pEntry;
};

#endif /* DIRINFO_H_ */
