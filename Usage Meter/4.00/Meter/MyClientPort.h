// MyClienPort.h: interface for the CMyClienPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCLIENPORT_H__48202C58_7B88_4BA0_846C_7F4733D1784C__INCLUDED_)
#define AFX_MYCLIENPORT_H__48202C58_7B88_4BA0_846C_7F4733D1784C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyLogFile.h"
#include "resource.h"


class CMyClientPort  : public CMyLogFile
{
public:
			CMyClientPort();
	virtual ~CMyClientPort();

public:
	//fun
	void	IsServerRunning();
	void	GrantPrivilages();
protected:
	//ver
	//DWORD	m_client_count;
	//DWORD	m_id;
};

#endif // !defined(AFX_MYCLIENPORT_H__48202C58_7B88_4BA0_846C_7F4733D1784C__INCLUDED_)
