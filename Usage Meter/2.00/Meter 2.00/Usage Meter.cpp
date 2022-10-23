// Usage Meter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Usage Meter.h"
#include "MyLogFile.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsageMeterApp
BEGIN_MESSAGE_MAP(CUsageMeterApp, CWinApp)
	//{{AFX_MSG_MAP(CUsageMeterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsageMeterApp construction

CUsageMeterApp::CUsageMeterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUsageMeterApp object
CUsageMeterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUsageMeterApp initialization

BOOL CUsageMeterApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	if(HasPreInstance()==FALSE)
	{
	CMainDlg dlg ;
	m_pMainWnd =&dlg;
	dlg.DoModal();
	}
	return FALSE;
}

BOOL CUsageMeterApp::PreTranslateMessage(MSG* pMsg) 
{
#ifdef _DEBUG
#else
	// Detect Esc KeyPrees and bypass it
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==27)
		{ShowWindow(theApp.m_pMainWnd->m_hWnd,0);
		return 0;}
	}
#endif
return CWinApp::PreTranslateMessage(pMsg);
}

BOOL CUsageMeterApp::HasPreInstance()
{
#ifdef _DEBUG
	return FALSE;
#else
CMyLogFile  lf;
CWnd*		prewnd = CWnd::FindWindow("#32770", lf.CreateTitle());
	if(prewnd)
	{
		prewnd->ShowWindow(1);
		prewnd->SetForegroundWindow();
		return TRUE;
	}else{
		return FALSE;
	}
#endif
}
