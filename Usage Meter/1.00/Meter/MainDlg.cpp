//************ 10-07-2004 18:49 ****************

#include "stdafx.h"
#include "Usage Meter.h"
#include "MainDlg.h"
#include <Wininet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CAboutDlg dialog used for App About***********************************************************
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	CWnd**	m_my_handle;//pointer to CMainDlg CWnd*	m_about_dlg
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
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CMainDlg dialog*******************************************************************************
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
	DDX_Control(pDX, IDC_STATUS, m_status_lbl);
	DDX_Control(pDX, IDC_INT_LIST, m_Int_List);
	DDX_Control(pDX, IDC_WIN_LIST, m_Win_List);
	DDX_Control(pDX, IDC_TAB, m_Tab_Ctrl);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, OnSelchangingTab)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_FILE_VIEWER, OnFileViewer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers
BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{	CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);	

	StartUp();

	return TRUE;  
}
//------------------------------------------------------------------------------------------------
void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		ShowAboutBox();
	}else{
		CDialog::OnSysCommand(nID, lParam);
	}
}
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
	}else{
		CDialog::OnPaint();
	}
}
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//-------------------------------------------------------------------------------------------
LRESULT CMainDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
switch(message)
{
case ID_TRAY_ICON:
//Tray icon Msg
	if(lParam==WM_LBUTTONDOWN)
	{//LBUTTON DOWN
		ShowWindow(1);
		SetForegroundWindow();
		return 0;
	}
	if(lParam==WM_RBUTTONDOWN)
	{//LBUTTON DOWN
		delete m_pop_menu;
		m_pop_menu = new CMenu();
		m_pop_menu->CreatePopupMenu();
		if(IsWindowVisible())
		{
		m_pop_menu->AppendMenu( MF_STRING, ID_TRAY_SHOEHIDE,"Hide" );
		}else{
		m_pop_menu->AppendMenu( MF_STRING, ID_TRAY_SHOEHIDE,"Show" );
		}
		m_pop_menu->AppendMenu( MF_STRING, ID_FILE_VIEWER,"File Viewer" );
		m_pop_menu->AppendMenu( MF_SEPARATOR, NULL,"");
		m_pop_menu->AppendMenu( MF_STRING, ID_TRAY_ABOUT,"About..." );
		CPoint cur_point;
		GetCursorPos(&cur_point);
		m_pop_menu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,cur_point.x, cur_point.y,this);
		return 0;
	}
break;

case WM_COMMAND:
	switch(wParam)
	{//Tray menu commands
	case ID_TRAY_ABOUT:
		ShowAboutBox();
	break;
	case ID_TRAY_SHOEHIDE:
		if(IsWindowVisible()){
		ShowWindow(0);
		}else{
		ShowWindow(1);}
	break;
	}
break;

case WM_ENDSESSION:
//ShutDown,LogOff
	ShutDown();
}
	return CDialog::WindowProc(message, wParam, lParam);
}
//-------------------------------------------------------------------------------------------
void CMainDlg::OnClose() 
{
	ShowWindow(0);
}
//-------------------------------------------------------------------------------------------
void CMainDlg::OnOK() 
{
	ShowWindow(0);
}
//-------------------------------------------------------------------------------------------
void CMainDlg::OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult) 
{//Tab changed
	if(m_Tab_Ctrl.GetItemState(1,1) == 1)
	{//Internet
	m_Win_List.ShowWindow(0);
	m_Int_List.ShowWindow(1);
	m_select_tab = 0;
	}
	else
	{//Windows
	m_Win_List.ShowWindow(1);
	m_Int_List.ShowWindow(0);
	m_select_tab = 1;
	};

	TimerMain();
	*pResult = 0;
}
//-------------------------------------------------------------------------------------------
void CMainDlg::OnTimer(UINT nIDEvent) 
{//Timer Msges
int x,y;
	switch (nIDEvent)
	{
	case ID_MAIN_TIMER:
		TimerMain();
		break;
	case ID_HIDE_TIMER:
		KillTimer(ID_HIDE_TIMER);
		ShowWindow(0);
		//Posision Main Dlg
		x= m_my_api.RegGet(HKEY_CURRENT_USER,"x");
		y= m_my_api.RegGet(HKEY_CURRENT_USER,"y");
		if (x==0||y==0){ x=100 ;y=100;}
		SetWindowPos(&CWnd::wndTop,x,y,0,0,SWP_NOSIZE);
		break;
	case ID_SERVER_LINK_TIMER:
		//chek wether a server given privilage
		m_my_api.GrantPrivilages(this->m_hWnd);
		break;
	}
CDialog::OnTimer(nIDEvent);
}
//-------------------------------------------------------------------------------------------
void CMainDlg::SetUpDialog()
{
CRect dlg_rect;
CWnd* static_ctrl;

	GetClientRect(&dlg_rect);

	//Tab Cntl
	m_Tab_Ctrl.InsertItem(0,"Internet");
	m_Tab_Ctrl.InsertItem(1,"Windows");
	m_Tab_Ctrl.MoveWindow(5,6,dlg_rect.Width()-6,dlg_rect.Height()-40);
	//Static
	static_ctrl=GetDlgItem(IDC_STATIC);
	static_ctrl->SetWindowPos(&CWnd::wndTop ,10,32,dlg_rect.Width()-18,dlg_rect.Height()-73,SWP_SHOWWINDOW);
	//Create ListView Fonts
LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 13;
	strcpy(lf.lfFaceName, "Verdana");
	m_font_int.CreateFontIndirect(&lf);
	m_Int_List.SetFont(&m_font_int, TRUE);
	m_font_win.CreateFontIndirect(&lf);
	m_Win_List.SetFont(&m_font_win, TRUE);

	//SetUp listView
CListCtrl* p_list;
	for(int i=0;i<2;i++)
	{
	//Set pointer
	if(i==0)
	p_list = &m_Int_List;
	else
	p_list = &m_Win_List;
	ListView_SetExtendedListViewStyle(p_list->m_hWnd,LVS_EX_GRIDLINES| LVS_EX_FULLROWSELECT );
	p_list->SetTextColor(RGB(0,0,255));
	p_list->InsertColumn(1,"Log",LVCFMT_CENTER,40);
	p_list->InsertColumn(2,"Day",LVCFMT_CENTER,40);
	p_list->InsertColumn(3,"From To",LVCFMT_CENTER,145);
	p_list->InsertColumn(4,"Duration",LVCFMT_CENTER,80);
	p_list->InsertColumn(5,"User(s)",LVCFMT_LEFT,160);
	p_list->MoveWindow(12,35,dlg_rect.Width()-22,dlg_rect.Height()-78);
	}
	//Hide win list
	m_Win_List.ShowWindow(0);
}
//------------------------------------------------------------------------------------------------
void CMainDlg::SetUpTray(DWORD Task,char* tip,int size)
{
NOTIFYICONDATA nd;
	nd.cbSize=sizeof(nd);
	nd.uCallbackMessage=ID_TRAY_ICON;
	nd.hIcon=CDialog::GetIcon(false);
	nd.hWnd=this->m_hWnd;
	nd.uID=1;
	nd.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	strncpy(nd.szTip, tip ,size);
	Shell_NotifyIcon(Task, &nd);	
}
//------------------------------------------------------------------------------------------------
void CMainDlg::SaveWindowPos()
{
CRect dlg_rect;
	//Save pos
	GetWindowRect(&dlg_rect);
	m_my_api.RegSet(HKEY_CURRENT_USER,"x",dlg_rect.left);
	m_my_api.RegSet(HKEY_CURRENT_USER,"y",dlg_rect.top);
}
//------------------------------------------------------------------------------------------------
void CMainDlg::ShowAboutBox()
{
	if(m_about_dlg==NULL)
	{
CString s;
	CAboutDlg dlgAbout;
	dlgAbout.m_my_handle = &m_about_dlg;
	dlgAbout.DoModal();
	}
	else
	{
	m_about_dlg->SetForegroundWindow();
	}
}
//------------------------------------------------------------------------------------------------
void CMainDlg::ShutDown()
{	
	delete m_pop_menu;
	KillTimer(ID_SERVER_LINK_TIMER);
	KillTimer(ID_MAIN_TIMER);
	SetUpTray(NIM_DELETE,NULL,0);
	SaveWindowPos();
	m_my_api.RemoveUser();
	
	if(m_privilage==SERVER)
	{//Give privilage to running client to be a server
		if(m_my_api.GivePrivilage()==false)
		{//no clients to get privilage so I should save log
			//Remove connection status file
			TRY{m_file_con_info.Remove("E:\\Usage Log\\Disconnected");}CATCH( CFileException, e ){}END_CATCH
			TRY{m_file_con_info.Remove("E:\\Usage Log\\Connected");}CATCH( CFileException, e ){}END_CATCH

			CString temp_stop_time = m_my_api.GetTime();
			CString today=m_my_api.GetDay();
			//save windows usage
			CString temp_duration;
			m_my_api.TimeElapse(m_win_str_sec,&temp_stop_time,&temp_duration);
			m_my_api.Save_Win_Usage(today,m_win_str_time,temp_stop_time,temp_duration);
			//(save internet usage) This is only done if currently connected this connection will
			//terminate shortly after UsageMeter diminish this situation ocour when user log off
			//without disconnecting the internet
		DWORD contype;
			if(InternetGetConnectedState(&contype, NULL))
			{
				if((contype&INTERNET_CONNECTION_MODEM)==INTERNET_CONNECTION_MODEM)
				{
				m_my_api.TimeElapse(m_int_str_sec,&temp_stop_time,&temp_duration);
				m_my_api.Save_Int_Usage(today,m_int_str_time,temp_stop_time,temp_duration);
				}
			}
		}
	}
}
//------------------------------------------------------------------------------------------------
void CMainDlg::StartUp()
{
//common routine for any mode
	//Set counters reference
	m_win_counter.m_pstart_sec = &m_win_str_sec;
	m_int_counter.m_pstart_sec = &m_int_str_sec;
	//set popup menu pointer to NULL (it's safe)
	m_about_dlg= NULL;
	m_pop_menu = NULL;
	m_select_tab = 0;
	//Loas resources
	m_res_zerotime.LoadString(IDS_ZERO_TIME);
HINSTANCE rh = AfxGetResourceHandle();
	LoadString(rh,IDS_INTOFFLABLE,m_res_intofflable,50);
	LoadString(rh,IDS_INTCONLABLE,m_res_intconlable,50);
	LoadString(rh,IDS_WIN_LABLE,m_res_winlable,50);
	LoadString(rh,IDS_WIN_TIP,m_res_wintip,30);
	LoadString(rh,IDS_INTOFF_TIP,m_res_intofftip,30);
	LoadString(rh,IDS_INTCON_TIP,m_res_intcontip,30);
	//initialize inherited ojects
	m_my_api.IntServerPortObj(&m_privilage);
	m_my_api.IntLogFileObj(&m_Int_List,&m_Win_List,&m_internet_total,&m_windows_total,this);
	//Set up Dialog box
	SetUpDialog();
	//Set Tray Icon
	SetUpTray(NIM_ADD," Usage Meter \0",14);
	//Load log
	m_my_api.SetLogPath();
	m_my_api.LoadLog();
	//Posision window away from screen
	CRect r;
	::GetWindowRect(::GetDesktopWindow(),&r);
	SetWindowPos(&CWnd::wndTop,r.right+10,0,0,0,SWP_NOSIZE);
	//check server running
	m_my_api.IsServerRunning(&m_win_str_time);

CString temp_win_dur;

	if (m_privilage==SERVER)
	{//fresh start
	//Remove connection status file "Connected"
	TRY{m_file_con_info.Remove("E:\\Usage Log\\Connected");}CATCH( CFileException, e ){}END_CATCH
	m_file_con_info.Open("E:\\Usage Log\\Disconnected",CFile::modeCreate);
	m_file_con_info.Close();

	m_my_api.InitializeUserList();
	//initialize int start time
	m_int_str_time = m_res_zerotime;
	//Save windows start time
	m_win_str_time	= m_my_api.GetTime();
	m_win_counter.SetAt(&m_res_zerotime);
	temp_win_dur	= m_res_zerotime;
	}
	
	//At this point m_win_str_time can conver to seconds
	m_win_str_sec	= m_my_api.ToSeconds(&m_win_str_time);

	if (m_privilage==CLIENT)
	{
	//add current user to the registry
	m_my_api.AddUser();
	//Calculat win duration
	m_my_api.TimeElapse(m_win_str_sec,&m_my_api.GetTime(),&temp_win_dur);
	//Set starting poit for win counter
	m_win_counter.SetAt(&temp_win_dur);
	//I am a client client timer tick faster for comunication efficiency
	SetTimer(ID_SERVER_LINK_TIMER,500,0);
	}

	//Start main timer
	SetTimer(ID_MAIN_TIMER,1000,0);
	SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_HIGH,&temp_win_dur,&m_res_zerotime);

	//start hide timer
	SetTimer(ID_HIDE_TIMER,100,0);
}
//------------------------------------------------------------------------------------------------
void CMainDlg::SetLable(int mode,CString* win_duration,CString* int_duration)
{
static CString label="";

if(m_select_tab == 1)
{//Windows tab selected
	label.Format(m_res_winlable,*win_duration,m_windows_total);
	m_status_lbl.SetWindowText(label);
}else{
//Internet tab selected
	if(mode==ID_MODE_CONECT)
	{
		label.Format(m_res_intconlable,*int_duration,m_internet_total);
		m_status_lbl.SetWindowText(label);
	}else{
		label.Format(m_res_intofflable,m_internet_total);
		m_status_lbl.SetWindowText(label);
	}
}
}
//------------------------------------------------------------------------------------------------
void CMainDlg::SetTip(int mode,int prayority,CString* win_duration,CString* int_duration)
{
static int count=0;

	if(prayority!=ID_TIP_PRAYORITY_HIGH)
	{	if(count<5)
		{count++;
		return;}
	}
	count=0;
	
static CString fulltip;
static CString wintip;

	wintip.Format(m_res_wintip,*win_duration);

	if(mode==ID_MODE_CONECT)
	{
		fulltip.Format(m_res_intcontip,*int_duration,wintip);
	}else{
		fulltip.Format(m_res_intofftip,m_internet_total,wintip);
	}

int l=fulltip.GetLength()+1;
	SetUpTray(NIM_MODIFY,fulltip.GetBuffer(l),l);
}
//------------------------------------------------------------------------------------------------
#ifdef _DEBUG
bool CMainDlg::Fake_Connection()
{
DWORD i;
	i=m_my_api.RegGet(HKEY_LOCAL_MACHINE,"Connected");
	if(i==1)
		return true;
	return false;
}
#endif
//------------------------------------------------------------------------------------------------
void CMainDlg::TimerMain()
{
#ifdef _DEBUG
bool			connected;
#else
BOOL			connected;
#endif
DWORD			contype;
static bool		swap_dct=false;
bool			day_changed,month_changed;
CString			today, now, previ_day;
static CString	temp_win_duration;
static CString	temp_int_duration = m_res_zerotime;
	
#ifdef _DEBUG
	connected = Fake_Connection();
	if(connected==TRUE)
	contype =  INTERNET_CONNECTION_MODEM; 	
	else
	contype = 0;
#else
	connected = InternetGetConnectedState(&contype, NULL);
	if(connected==TRUE)
	contype = (contype & INTERNET_CONNECTION_MODEM); 	
	else
	contype = 0;
#endif

	today				= m_my_api.GetDay(&day_changed,&previ_day);
	month_changed		= m_my_api.DetectMonChange();
	now					= m_my_api.GetTime();

if(m_privilage==SERVER)
{//++++++++++++++++++++++++++++++++++++ (IF SERVER) ++++++++++++++++++++++++++++++++++++++++++++
//DETECT CHANGE OF DAY
	if(day_changed)
	{
		if (contype==INTERNET_CONNECTION_MODEM)
		{//Save Internet log
			m_my_api.TimeElapse(m_int_str_sec,&now,&temp_int_duration);
			m_my_api.Save_Int_Usage(previ_day,m_int_str_time,now,temp_int_duration);
			m_int_str_time = now;
			m_int_str_sec=m_my_api.ToSeconds(&m_int_str_time);
			m_int_counter.SetAt(&m_res_zerotime);
		}
		//Save Windows log
		m_my_api.TimeElapse(m_win_str_sec,&now,&temp_win_duration);
		m_my_api.Save_Win_Usage(previ_day,m_win_str_time,now,temp_win_duration);
		m_win_str_time		= now;
		m_win_str_sec=m_my_api.ToSeconds(&m_win_str_time);
		m_win_counter.SetAt(&m_res_zerotime);
			if (month_changed)
			{//Month shift
				m_my_api.SetLogPath();
			}
		//load log file
		m_my_api.LoadLog();
	}

//CHECK CONNECTION STATE
	if (contype==INTERNET_CONNECTION_MODEM)
	{
		if (swap_dct==false){
		swap_dct=true;
//-----------JUST CONNECTED----------------------
		m_int_str_time = now;
		m_int_str_sec = m_my_api.ToSeconds(&m_int_str_time);
		m_int_counter.SetAt(&m_res_zerotime);
		SetTip(ID_MODE_CONECT,ID_TIP_PRAYORITY_HIGH,&temp_win_duration,&temp_int_duration);
		//Create "Connected" file to show connection state
		TRY{m_file_con_info.Remove("E:\\Usage Log\\Disconnected");}CATCH( CFileException, e ){}END_CATCH
		m_file_con_info.Open("E:\\Usage Log\\Connected",CFile::modeCreate);
		m_file_con_info.Close();
//-----------JUST CONNECTED-----------------------
		}
	}else{
		if (swap_dct==true){
		swap_dct=false;
//---------JUST DISCONNECTED----------------------
		//Save Internet log
		m_my_api.TimeElapse(m_int_str_sec,&now,&temp_int_duration);
		m_my_api.Save_Int_Usage(today,m_int_str_time,now,temp_int_duration);
		SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_HIGH,&temp_win_duration,&temp_int_duration);
		//Create "Disconnected" file to show connection state
		TRY{m_file_con_info.Remove("E:\\Usage Log\\Connected");}CATCH( CFileException, e ){}END_CATCH
		m_file_con_info.Open("E:\\Usage Log\\Disconnected",CFile::modeCreate);
		m_file_con_info.Close();
//---------JUST DISCONNECTED----------------------
		}}

//GIVE DATA AND ANSWER TO CLIENT IF NESSASARY
	m_my_api.SayServerActive(&m_win_str_time);

}else{
//+++++++++++++++++++++++++++++++++++++++ (IF CLIENT) ++++++++++++++++++++++++++++++++++++++++++

	//DETECT CHANGE OF DAY
	if(day_changed)
	{
		if (contype==INTERNET_CONNECTION_MODEM)
		{
		m_int_str_time = now;
		m_int_str_sec=m_my_api.ToSeconds(&m_int_str_time);
		m_int_counter.SetAt(&m_res_zerotime);
		}

		m_win_str_time = now;
		m_win_str_sec = m_my_api.ToSeconds(&m_win_str_time);
		m_win_counter.SetAt(&m_res_zerotime);

		if (month_changed)
			m_my_api.SetLogPath();
			
		//Wait untill server setup the log file
		::Sleep(1100);
		m_my_api.LoadLog();
	}

//CHECK CONNECTION STATE
	if (contype==INTERNET_CONNECTION_MODEM)
	{
		if (swap_dct==false){
		swap_dct=true;
//-----------JUST CONNECTED----------------------
		m_int_str_time = now;
		m_int_str_sec=m_my_api.ToSeconds(&m_int_str_time);
		m_int_counter.SetAt(&m_res_zerotime);
		SetTip(ID_MODE_CONECT,ID_TIP_PRAYORITY_HIGH,&temp_win_duration,&temp_int_duration);
//-----------JUST CONNECTED----------------------
		}
	}else{
		if (swap_dct==true){
		swap_dct=false;
//---------JUST DISCONNECTED----------------------
		//Wait untill server setup file
		::Sleep(1100);
		m_my_api.LoadLog();
		SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_HIGH,&temp_win_duration,&temp_int_duration);
//---------JUST DISCONNECTED----------------------
		}}
}
//+++++++++++++++++++++++++++ (COMMON TO SERVER ANFD CLIENT) +++++++++++++++++++++++++++++++

//Setup Tip
	//Do Rough calculation of duration (For eficiency)
	m_win_counter.Incriment(&temp_win_duration);
	if (swap_dct==true){
	//Connected
	//Do Rough calculation of duration (For eficiency)
	m_int_counter.Incriment(&temp_int_duration);
	SetTip(ID_MODE_CONECT , ID_TIP_PRAYORITY_NORMAL,&temp_win_duration,&temp_int_duration);
	}else{
	//Disconnected
	SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_NORMAL,&temp_win_duration,&temp_int_duration);
	}
//Setup label
	if (!IsWindowVisible())
		return ;//Execut only if visible
	if (swap_dct==true){
	//Connected
	SetLable(ID_MODE_CONECT,&temp_win_duration,&temp_int_duration);
	}else{
	//Disconnected
	SetLable(ID_MODE_DESCONECT,&temp_win_duration,&temp_int_duration);
	}
}
//------------------------------------------------------------------------------------------------
void CMainDlg::OnFileViewer() 
{
char	c[100];
CString	Path;
int		len,index;
	//Get app path
	GetModuleFileName(NULL,c,100);
	Path = c;
	len = Path.GetLength();
	index = FindLatsSlash(&Path);
	Path = Path.Left(index);
	Path = Path + "\\Viewer.exe";
	
STARTUPINFO si;
PROCESS_INFORMATION pi;
	memset(&si,0,sizeof(STARTUPINFO));
	si.wShowWindow=1;
	si.cb=sizeof(STARTUPINFO);
	si.dwFlags=STARTF_USESTDHANDLES;

	if(CreateProcess(Path.GetBuffer(Path.GetLength()),NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi)==0)
		::MessageBox(this->m_hWnd,"File Viewer cannot be load !    ","Usage Meter",MB_OK|MB_ICONEXCLAMATION);
}
//------------------------------------------------------------------------------------------------
int CMainDlg::FindLatsSlash(CString *path)
{
char*	p;
int		len;
	len = path->GetLength()-1;
	p = path->GetBuffer(len);
	p=p+len;
	for(int i=len;i>0;i--)
	{
		if(*p=='\\')
			return i;
		p--;
	}
	return -1;
}

// CAboutDlg dialog used for App About***********************************************************
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

//------------------------------------------------------------------------------------------------
void CAboutDlg::OnClose() 
{//Set pointer to CAboutDlg handle to NULL
	*m_my_handle=NULL;
	CDialog::OnClose();
}
//------------------------------------------------------------------------------------------------
void CAboutDlg::OnOK() 
{//Set pointer to CAboutDlg handle to NULL
	*m_my_handle=NULL;
	CDialog::OnOK();
}
//------------------------------------------------------------------------------------------------
BOOL CAboutDlg::OnInitDialog()
{//Give CAboutDlg handle to CMainDlg
	*m_my_handle=this;
	return TRUE;  
}
