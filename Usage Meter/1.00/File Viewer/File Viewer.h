// File Viewer.h : main header file for the FILE VIEWER application
//

#if !defined(AFX_FILEVIEWER_H__20BFA43A_8433_4BC4_89B2_3AC510E7EAA4__INCLUDED_)
#define AFX_FILEVIEWER_H__20BFA43A_8433_4BC4_89B2_3AC510E7EAA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileViewerApp:
// See File Viewer.cpp for the implementation of this class
//

class CFileViewerApp : public CWinApp
{
public:
	CFileViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileViewerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEVIEWER_H__20BFA43A_8433_4BC4_89B2_3AC510E7EAA4__INCLUDED_)
