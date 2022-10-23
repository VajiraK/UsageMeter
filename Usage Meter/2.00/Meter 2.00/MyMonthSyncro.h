// MyMonthSyncro.h: interface for the CMyMonthSyncro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMONTHSYNCRO_H__2C321E6D_C6A7_4F11_8AC6_4C92367B985B__INCLUDED_)
#define AFX_MYMONTHSYNCRO_H__2C321E6D_C6A7_4F11_8AC6_4C92367B985B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyTimeMath.h"

class CMyMonthSyncro : public CMyTimeMath
{
public:
	bool	DetectMonChange();
protected:
			CMyMonthSyncro();
	CString NumToMothname(int monnum);
	int		GetSystemMonth();
private:
	DWORD	m_regmonth;
};

#endif // !defined(AFX_MYMONTHSYNCRO_H__2C321E6D_C6A7_4F11_8AC6_4C92367B985B__INCLUDED_)
