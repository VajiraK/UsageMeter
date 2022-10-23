// MyUser.h: interface for the CMyUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYUSER_H__0EE5ADCE_230A_4D20_AEE4_A955CC7D07BB__INCLUDED_)
#define AFX_MYUSER_H__0EE5ADCE_230A_4D20_AEE4_A955CC7D07BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyMonthSyncro.h"

class CMyUser : public CMyMonthSyncro
{
public:
	void	InitializeUserList();
	void	RemoveUser();
	void	AddUser();
protected:
	CString GetWinUsers();
	CString GetIntUsers();
	void	Split(CString* data,CStringArray* arr,char delemiter);
private:
	CString GetCurrentUser();
};

#endif // !defined(AFX_MYUSER_H__0EE5ADCE_230A_4D20_AEE4_A955CC7D07BB__INCLUDED_)
