// MyLogPath.h: interface for the CMyLogFolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLOGPATH_H__80EC3583_F35A_417D_826C_7A0FA5C90646__INCLUDED_)
#define AFX_MYLOGFOLDER_H__80EC3583_F35A_417D_826C_7A0FA5C90646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "MyMainWnd.h"
#include "MyUser.h"

class CMyLogPath : public CMyUser
{
public:
			CMyLogPath();
	virtual ~CMyLogPath();
	bool	GetLogPath(char* path,DWORD size,DWORD* len);

private:

	void	AddFileName(char* path,DWORD* len);
	bool	IsFolderExist(char* path,DWORD* len);
	bool	SetLogFolder();
};

#endif // !defined(AFX_MYLOGFOLDER_H__80EC3583_F35A_417D_826C_7A0FA5C90646__INCLUDED_)
