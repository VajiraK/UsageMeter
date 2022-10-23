// Utility.h : main header file for the UTILITY application
//

#if !defined(AFX_UTILITY_H__4C930AB1_52F4_41C4_AAE5_C14075B6D6B2__INCLUDED_)
#define AFX_UTILITY_H__4C930AB1_52F4_41C4_AAE5_C14075B6D6B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUtilityApp:
// See Utility.cpp for the implementation of this class
//

class CUtilityApp : public CWinApp
{
public:
	CUtilityApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUtilityApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUtilityApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UTILITY_H__4C930AB1_52F4_41C4_AAE5_C14075B6D6B2__INCLUDED_)
