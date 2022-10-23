// MyRegistry.h: interface for the CMyRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYREGISTRY_H__532C276B_C25D_402A_9CC3_885626E63C88__INCLUDED_)
#define AFX_MYREGISTRY_H__532C276B_C25D_402A_9CC3_885626E63C88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyRegistry  
{
public:
			CMyRegistry();//constructor
	void	RegSet(HKEY Hive,char* ValueName,DWORD Value);
	void	RegSet(HKEY Hive,char* ValueName,char* Value,DWORD size);
	DWORD	RegGet(HKEY Hive,char* ValueName);
	void	RegGet(HKEY Hive,char* ValueName,CString* strval);
private:
	char*	m_reg_key;
};
#endif // !defined(AFX_MYREGISTRY_H__532C276B_C25D_402A_9CC3_885626E63C88__INCLUDED_)
