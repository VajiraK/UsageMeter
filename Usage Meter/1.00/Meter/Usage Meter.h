// Usage Meter.h : main header file for the USAGE METER application
//

#if !defined(AFX_USAGEMETER_H__A78CEC0C_5E17_47F5_BDC6_3F47D12423AD__INCLUDED_)
#define AFX_USAGEMETER_H__A78CEC0C_5E17_47F5_BDC6_3F47D12423AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "MainDlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CUsageMeterApp:
// See Usage Meter.cpp for the implementation of this class
//

class CUsageMeterApp : public CWinApp
{
public:
	CUsageMeterApp();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsageMeterApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUsageMeterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL HasPreInstance();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USAGEMETER_H__A78CEC0C_5E17_47F5_BDC6_3F47D12423AD__INCLUDED_)
