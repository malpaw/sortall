/*
 * dirinfo.h
 *
 *  Created on: 14-06-2012
 *      Author: albeert
 */

#ifndef DIRINFO_H_
#define DIRINFO_H_
//
//struct DirEntry
//{
//	char pszName[13];
//	struct DirEntry* pNextEntry;
//};

struct DirInfo
{
	char pszName[13]; // 8.3+zero
	struct DirInfo* pNextEntry;
};

#endif /* DIRINFO_H_ */
