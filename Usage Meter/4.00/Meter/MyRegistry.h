// MyRegistry.h: interface for the CMyRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYREGISTRY_H__360CCA6E_B48B_4BDF_A8D9_0C908048361A__INCLUDED_)
#define AFX_MYREGISTRY_H__360CCA6E_B48B_4BDF_A8D9_0C908048361A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyEventLog.h"

class CMyRegistry : public CMyEventLog
{
public:
			CMyRegistry();
	virtual ~CMyRegistry();
	//BINARY
	bool	RegSetBinary(HKEY Hive,char* ValueName,BYTE* Value,DWORD size);
	bool	RegGetBinary(HKEY Hive,char* ValueName,BYTE* binval,DWORD size);
	//CHAR
	bool	RegSet(HKEY Hive,char* ValueName,char* Value,DWORD size);
	bool	RegGet(HKEY Hive,char* ValueName,char* chrval,DWORD size,DWORD* len);
	//DWORD
	bool	RegSet(HKEY Hive,char* ValueName,DWORD Value);
	bool	RegGet(HKEY Hive,char* ValueName,DWORD* pvalue);

private:
	SECURITY_ATTRIBUTES m_secu_atri;
	char*				m_reg_key;
	HKEY				m_key_handle;
};

#endif // !defined(AFX_MYREGISTRY_H__360CCA6E_B48B_4BDF_A8D9_0C908048361A__INCLUDED_)
