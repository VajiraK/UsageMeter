// DlgPath.cpp : implementation file
//

#include "stdafx.h"
#include "usage meter.h"
#include "DlgPath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
CDlgPath::CDlgPath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPath)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
void CDlgPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPath)
	DDX_Control(pDX, IDC_EDIT_PATH, m_txt_path);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CDlgPath, CDialog)
	//{{AFX_MSG_MAP(CDlgPath)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
void CDlgPath::OnOK() 
{
WIN32_FIND_DATA fd;
char	path[255];
LPTSTR	msg;
CString	temp;
HANDLE	hfind;

	//Get window text
	int i = m_txt_path.GetWindowText(path,255);

	if(i==0)
	{//There is no text in the texbox
		::MessageBox(NULL,"Please enter the path!   ","Usage Meter",MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	//Add '*' this is needed
	if(path[i-1]=='\\')
		memcpy(path+i,"*\0",2);
	else
		memcpy(path+i,"\\*\0",3);

	hfind = FindFirstFile(path, &fd);
	if((hfind==INVALID_HANDLE_VALUE)||(path[1]!=':'))
	{//Folder creation fails
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,GetLastError(),MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),(LPTSTR)&msg,0,NULL);
		temp.Format("%s%s","Unable to locate specified folder, Please check the path !     \r\n System Error - ",msg);
		::MessageBox(NULL,temp,"Usage Meter",MB_OK|MB_ICONEXCLAMATION);
		LocalFree(msg);
	}else{
		FindClose(hfind);
		KillTimer(TIMER_GET_PATH);
		m_bypass = true;
		m_errer = false;
		*m_plogpath = path;
		m_clsreg.RegSet(HKEY_LOCAL_MACHINE,"LogFolder",m_plogpath->GetBuffer(m_plogpath->GetLength()),m_plogpath->GetLength());
		m_clsreg.RegSet(HKEY_LOCAL_MACHINE,"PathPort",MSG_GOT_PATH);
		MySleep();
		CDialog::OnOK();
	}
}
//---------------------------------------------------------------------------------------------------------
void CDlgPath::OnCancel() 
{
	KillTimer(TIMER_GET_PATH);
	m_bypass = true;
	m_clsreg.RegSet(HKEY_LOCAL_MACHINE,"PathPort",MSG_PATH_ERROR);
	m_errer = true;
	CDialog::OnCancel();
}
//---------------------------------------------------------------------------------------------------------
BOOL CDlgPath::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_clsreg.RegSet(HKEY_LOCAL_MACHINE,"PathPort",MSG_INVALID);
	SetTimer(TIMER_GET_PATH,500,0);	
	return TRUE;  
}
//---------------------------------------------------------------------------------------------------------
void CDlgPath::OnTimer(UINT nIDEvent) 
{
	if(m_bypass!=true)
	{
		if(TIMER_GET_PATH==nIDEvent)
		{
			if(m_clsreg.RegGet(HKEY_LOCAL_MACHINE,"PathPort")==MSG_GOT_PATH)
			{//Some one has setup the path
				KillTimer(TIMER_GET_PATH);
				m_errer = false;
				//sleep a while if client becauose server allway update the file
				MySleep();
				char	czusers[100];
				DWORD	size = 100;
				m_clsreg.RegGet(HKEY_LOCAL_MACHINE,"LogFolder",czusers,&size);
				*m_plogpath = czusers;
				CDialog::EndDialog(0);
			}
			if(m_clsreg.RegGet(HKEY_LOCAL_MACHINE,"PathPort")==MSG_PATH_ERROR)
			{
				KillTimer(TIMER_GET_PATH);
				m_errer = true;
				CDialog::EndDialog(0);
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}
//---------------------------------------------------------------------------------------------------------
void CDlgPath::MySleep()
{
	if(*m_pprivilage==CLIENT)
	{
		this->ShowWindow(0);
		::Sleep(1100);
	}
}
