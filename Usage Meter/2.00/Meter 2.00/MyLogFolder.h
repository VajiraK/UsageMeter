// MyLogFolder.h: interface for the CMyPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPATH_H__B281C45E_BC3A_4A34_9950_9F2F77ADD7F5__INCLUDED_)
#define AFX_MYPATH_H__B281C45E_BC3A_4A34_9950_9F2F77ADD7F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyUser.h"

class CMyLogFolder : public CMyUser
{
public:
	DWORD*	m_pprivilage;
			CMyLogFolder();
	virtual ~CMyLogFolder();
	bool	GetLogFolder(CString* plogfolder);
private:
	bool SetLogFolder(CString* plogfolder);
};

#endif // !defined(AFX_MYPATH_H__B281C45E_BC3A_4A34_9950_9F2F77ADD7F5__INCLUDED_)
