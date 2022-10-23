// MyServerPort.h: interface for the CMyLinker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEMULATOR_H__298A481D_BBE8_4839_8631_5AD1A503F796__INCLUDED_)
#define AFX_MYEMULATOR_H__298A481D_BBE8_4839_8631_5AD1A503F796__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyClientPort.h"

class CMyServerPort : public CMyClientPort
{
public:
	void	IntServerPortObj(DWORD* prilageref);
	bool	GivePrivilage();
	void	SayServerActive(char* winstart,DWORD winroughdu);	
};

#endif // !defined(AFX_MYEMULATOR_H__298A481D_BBE8_4839_8631_5AD1A503F796__INCLUDED_)
