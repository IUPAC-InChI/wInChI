#ifndef __UTIL_WINCHI_H__
#define __UTIL_WINCHI_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

inline BOOL FileExists(const CString& PathAndFileName)
{
	CFileStatus FileStatus;
	return CFile::GetStatus(PathAndFileName, FileStatus);
}

#endif
