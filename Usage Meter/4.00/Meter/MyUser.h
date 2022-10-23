// MyUser.h: interface for the CMyUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYUSER_H__9A621CD4_B27A_4777_AACD_9BD6A3FEEC49__INCLUDED_)
#define AFX_MYUSER_H__9A621CD4_B27A_4777_AACD_9BD6A3FEEC49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyDate.h"

class CMyUser :  public CMyDate
{
public:
			CMyUser();
	virtual	~CMyUser();
	void	InitializeUserList();
	void	SetActiveUsers();
	void	SetLogonUsers();
	void	RemoveUser();
	void	AddUser();
	bool	FindUser(char *list, char *user, WORD listlen, WORD userlen, WORD* srtpoint=NULL, WORD* endpoint=NULL);
	char	m_users[250];

private:
	void FormatUserList();
};

#endif // !defined(AFX_MYUSER_H__9A621CD4_B27A_4777_AACD_9BD6A3FEEC49__INCLUDED_)
