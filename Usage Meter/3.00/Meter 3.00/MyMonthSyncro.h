// MyMonthSyncro.h: interface for the CMyMonthSyncro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMONTHSYNCRO_H__0FED8FE6_2F9E_442C_9F43_BA373C3B73FE__INCLUDED_)
#define AFX_MYMONTHSYNCRO_H__0FED8FE6_2F9E_442C_9F43_BA373C3B73FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyRegistry.h"

class CMyMonthSyncro : public CMyRegistry
{
public:
			CMyMonthSyncro();
	virtual ~CMyMonthSyncro();
	DWORD	DetectMonChange(bool* pchanged);


};

#endif // !defined(AFX_MYMONTHSYNCRO_H__0FED8FE6_2F9E_442C_9F43_BA373C3B73FE__INCLUDED_)
