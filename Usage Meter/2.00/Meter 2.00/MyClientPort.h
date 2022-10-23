// MyClientPort.h: interface for the CMyClientPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCLIENTPORT_H__44917915_42A4_41B4_BC44_6DCCD69AA0CB__INCLUDED_)
#define AFX_MYCLIENTPORT_H__44917915_42A4_41B4_BC44_6DCCD69AA0CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyLogFile.h"
#include "MyCounter.h"

class CMyClientPort : public CMyLogFile
{
public:
	//fun
	void	IsServerRunning(char* winstart,DWORD* winroughdu);
	void	GrantPrivilages(HWND main_dlg);
protected:
	//ver
	DWORD	m_client_count;
	DWORD*	m_pprivilage;//pointer to MainDlg m_privilage
	DWORD	m_id;
};

#endif // !defined(AFX_MYCLIENTPORT_H__44917915_42A4_41B4_BC44_6DCCD69AA0CB__INCLUDED_)
