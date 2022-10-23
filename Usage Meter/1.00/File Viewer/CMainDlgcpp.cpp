// CMainDlgcpp.cpp : implementation file
//

#include "stdafx.h"
#include "File Viewer.h"
#include "CMainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_INT_STATUS, m_int_lable);
	DDX_Control(pDX, IDC_WIN_STATUS, m_win_lable);
	DDX_Control(pDX, IDC_WIN_LIST, m_Win_List);
	DDX_Control(pDX, IDC_INT_LIST, m_Int_List);
	DDX_Control(pDX, IDC_TAB, m_Tab_Ctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(IDM_ABOUTBOX, OnAboutbox)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, OnSelchangingTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetUpDialog();
	m_logfilobj.IntLogFileObj(&m_Int_List,&m_Win_List,&m_int_lable,&m_win_lable,this);
	m_logfilobj.AssosiateFiles();
	
	if(com_line.IsEmpty()==FALSE)
		m_logfilobj.LoadLogFile(com_line);	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		OnAboutbox();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//-------------------------------------------------------------------------------
void CMainDlg::SetUpDialog()
{
CRect dlg_rect;
CWnd* static_ctrl;

	GetClientRect(&dlg_rect);
	//Hide win lable
	m_win_lable.ShowWindow(0);
	//Tab Cntl
	m_Tab_Ctrl.InsertItem(0,"Internet");
	m_Tab_Ctrl.InsertItem(1,"Windows");
	m_Tab_Ctrl.MoveWindow(5,6,dlg_rect.Width()-6,dlg_rect.Height()-40);
	//Static
	static_ctrl=GetDlgItem(IDC_STATIC);
	static_ctrl->SetWindowPos(&CWnd::wndTop ,10,32,dlg_rect.Width()-18,dlg_rect.Height()-73,SWP_SHOWWINDOW);
	//Int ListView
LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 13;
	strcpy(lf.lfFaceName, "Verdana");
	m_font_int.CreateFontIndirect(&lf);
	m_Int_List.SetTextColor(RGB(0,0,255));
	m_Int_List.SetFont(&m_font_int, TRUE);
	ListView_SetExtendedListViewStyle(m_Int_List.m_hWnd,LVS_EX_GRIDLINES| LVS_EX_FULLROWSELECT );
	m_Int_List.InsertColumn(1,"Log",LVCFMT_CENTER,40);
	m_Int_List.InsertColumn(2,"Day",LVCFMT_CENTER,40);
	m_Int_List.InsertColumn(3,"From To",LVCFMT_CENTER,145);
	m_Int_List.InsertColumn(4,"Duration",LVCFMT_CENTER,80);
	m_Int_List.InsertColumn(5,"User(s)",LVCFMT_LEFT,120);
	//Win ListView
	m_font_win.CreateFontIndirect(&lf);
	m_Win_List.SetTextColor(RGB(0,0,255));
	m_Win_List.SetFont(&m_font_win, TRUE);
	m_Win_List.ShowWindow(0);
	ListView_SetExtendedListViewStyle(m_Win_List.m_hWnd,LVS_EX_GRIDLINES| LVS_EX_FULLROWSELECT );
	m_Win_List.InsertColumn(1,"Log",LVCFMT_CENTER,40);
	m_Win_List.InsertColumn(2,"Day",LVCFMT_CENTER,40);
	m_Win_List.InsertColumn(3,"From To",LVCFMT_CENTER,145);
	m_Win_List.InsertColumn(4,"Duration",LVCFMT_CENTER,80);
	m_Win_List.InsertColumn(5,"User(s)",LVCFMT_LEFT,120);
	m_Int_List.MoveWindow(12,35,dlg_rect.Width()-22,dlg_rect.Height()-78);
	m_Win_List.MoveWindow(12,35,dlg_rect.Width()-22,dlg_rect.Height()-78);
}
//----------------------------------------------------------------------------------
void CMainDlg::OnFileClose() 
{
	CDialog::OnCancel();
}
//----------------------------------------------------------------------------------
void CMainDlg::OnAboutbox() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();	
}
//----------------------------------------------------------------------------------
void CMainDlg::OnFileOpen() 
{
CFileDialog fd(true);

	fd.m_ofn.nMaxFile=100;
	fd.m_ofn.lpstrTitle="Select a file...";
	fd.m_ofn.lpstrFilter="Usage Log File(s)\0*.iuf\0\0";
	fd.m_ofn.nFilterIndex=0;
	fd.DoModal();

CString s = fd.m_ofn.lpstrFile;
	if(s.IsEmpty()==FALSE)
		m_logfilobj.LoadLogFile(fd.m_ofn.lpstrFile);
}
//----------------------------------------------------------------------------------
void CMainDlg::OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_Tab_Ctrl.GetItemState(1,1) == 1)
	{//Internet
	m_win_lable.ShowWindow(0);
	m_int_lable.ShowWindow(1);
	m_Win_List.ShowWindow(0);
	m_Int_List.ShowWindow(1);
	}
	else
	{//Windows
	m_win_lable.ShowWindow(1);
	m_int_lable.ShowWindow(0);
	m_Win_List.ShowWindow(1);
	m_Int_List.ShowWindow(0);
	};

	*pResult = 0;
}

