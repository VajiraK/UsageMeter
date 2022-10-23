//************ 10-07-2004 18:49 ****************

#include "stdafx.h"
#include "Usage Meter.h"
#include "MainDlg.h"
#include "DlgBeepSetting.h"
#include "MyListView.h"
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
	ON_BN_CLICKED(ID_BEEP_SET, OnBeepSet)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers
BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	/*CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{	CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}*/
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
		m_pop_menu->SetDefaultItem(0,TRUE);
		m_pop_menu->AppendMenu( MF_STRING, ID_FILE_VIEWER,"File Viewer" );
		m_pop_menu->AppendMenu( MF_SEPARATOR, NULL,"");
		m_pop_menu->AppendMenu( MF_STRING, ID_TRAY_ABOUT,"About..." );
		CPoint cur_point;
		GetCursorPos(&cur_point);
		SetForegroundWindow();
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
	::ShowWindow(m_hwin_list,0);
	::ShowWindow(m_hint_list,1);
	m_select_tab = 0;
	}
	else
	{//Windows
	::ShowWindow(m_hwin_list,1);
	::ShowWindow(m_hint_list,0);
	m_select_tab = 1;
	};

	//TimerMain();
	*pResult = 0;
}
//-------------------------------------------------------------------------------------------
void CMainDlg::OnTimer(UINT nIDEvent) 
{//Timer Msges
int			x,y;
static BYTE	i;
	switch (nIDEvent)
	{
	case TIMER_MAIN:
		TimerMain();
		break;
	case TIMER_HIDE:
		if(i==2)//Hide timer ticks 3 times to ensure the mighty Usage Meter is hidden(ha... ha...)
			KillTimer(TIMER_HIDE);
		i++;
		ShowWindow(0);
		//Posision Main Dlg
		x= m_my_api.RegGet(HKEY_CURRENT_USER,"x");
		y= m_my_api.RegGet(HKEY_CURRENT_USER,"y");
		if (x==0||y==0){ x=100 ;y=100;}
		SetWindowPos(&CWnd::wndTop,x,y,0,0,SWP_NOSIZE);
		break;
	case TIMER_SERVER_LINK:
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

	//Add about item to system menu
	HMENU hsys_menu = ::GetSystemMenu(this->m_hWnd,FALSE);
	::AppendMenu(hsys_menu,MF_SEPARATOR,NULL,NULL);
	::AppendMenu(hsys_menu,MF_STRING, IDM_ABOUTBOX,"About...");
	
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
	m_font_int = ::CreateFontIndirect(&lf);
	m_font_win = ::CreateFontIndirect(&lf);
	//SetUp listView
CMyListView list;
	list.SetupListview(m_hwin_list,m_hint_list,m_font_win,m_font_int);

	//Hide win list
	::ShowWindow(m_hwin_list,0);
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
	KillTimer(TIMER_SERVER_LINK);
	KillTimer(TIMER_MAIN);
	SetUpTray(NIM_DELETE,NULL,0);
	SaveWindowPos();
	
	if(m_privilage==SERVER)
	{//Give privilage to running client to be a server
		if(m_my_api.GivePrivilage()==false)
		{//no clients to get privilage so I should save log
			//Remove connection status file
			m_my_api.SetStatusFile(CLEAR_STATUS);
			m_my_api.GetTime(m_now);
			DAY_STRUCT today;
			m_my_api.GetDay(&today);
			//save windows usage
			//m_my_api.TimeElapse(m_win_str_sec,m_now,m_temp_duration);
			m_win_counter.GetDuration(m_temp_rugh_dura);
			m_my_api.Save_Win_Usage(&today,m_win_str_time,m_now,m_temp_rugh_dura,m_temp_rugh_dura);

			//(save internet usage) This is only done if currently connected this connection will
			//terminate shortly after UsageMeter diminish this situation ocour when user log off
			//without disconnecting the internet
		DWORD contype;
			if(InternetGetConnectedState(&contype, NULL))
			{
				if((contype&INTERNET_CONNECTION_MODEM)==INTERNET_CONNECTION_MODEM)
				{
				//m_my_api.TimeElapse(m_int_str_sec,m_now,m_temp_duration);
				m_int_counter.GetDuration(m_temp_rugh_dura);
				m_my_api.Save_Int_Usage(&today,m_int_str_time,m_now,m_temp_rugh_dura,m_temp_rugh_dura);
				}
			}
		}
	}

	::DeleteObject(m_font_win);
	::DeleteObject(m_font_int);
	m_my_api.RemoveUser();
}
//------------------------------------------------------------------------------------------------
void CMainDlg::StartUp()
{
//common routine for any mode
	//Get ListView Handles
	m_hwin_list = ::GetDlgItem(this->m_hWnd,IDC_WIN_LIST);
	m_hint_list = ::GetDlgItem(this->m_hWnd,IDC_INT_LIST);
	//Set counters reference
	m_win_counter.m_pstart_sec = &m_win_str_sec;
	m_int_counter.m_pstart_sec = &m_int_str_sec;
	//Check beep settings and set beeps
	SetBeep(true,true);
	//set popup menu pointer to NULL (it's safer)
	m_about_dlg = NULL;
	m_pop_menu = NULL;
	m_select_tab = 0;
	//Load resources
	memcpy(m_res_zerotime,"00:00:00\0",9);
	memcpy(m_temp_duration,m_res_zerotime,9);
	memcpy(m_temp_rugh_dura,m_res_zerotime,9);
	memcpy(m_win_str_time,m_res_zerotime,9);
	memcpy(m_int_str_time,m_res_zerotime,9);
	//Fill m_res_tip_text buffer (Bit tricky)**********
	memcpy(m_res_tip_text,"Internet Usage : 000:00:00\n\rWindows running : 00:00:00\0",55);
	m_win_duration = m_res_tip_text + 46;//Directly send a part of buffer to counters (Efficiancy man Efficiancy...)
	m_int_total    = m_res_tip_text + 17;
	memcpy(m_res_tip_text+56,"Connected : 00:00:00\n\rWindows running : 00:00:00\0",49);
	m_int_duration = m_res_tip_text+68;
	//Fill m_res_label_text buffer
	memcpy(m_res_label_text,"Offline     |     Total - 000:00:00\0",36);
	memcpy(m_res_label_text+37,"Connected - 00:00:00     |     Total - 000:00:00\0",49);
	memcpy(m_res_label_text+86,"Running - 00:00:00     |     Total - 000:00:00\0",47);
	m_win_total = m_res_label_text + 123;
	//initialize ServerPortObj
	m_my_api.IntServerPortObj(&m_privilage);
	//Write Run key
char	temp_path[_MAX_PATH];
DWORD	temp_len = _MAX_PATH;
	GetAppPath(temp_path,&temp_len,true);
	//Set up Dialog box
	SetUpDialog();
	//Set Tray Icon
	SetUpTray(NIM_ADD," Usage Meter \0",14);
	//Posision window away from screen
	RECT	r;
	::GetWindowRect(::GetDesktopWindow(),&r);
	::SetWindowPos(this->m_hWnd, HWND_BOTTOM,r.right+10,0,0,0,SWP_NOSIZE);
	//check server running
DWORD	temp_winroughdu;
	m_my_api.IsServerRunning(m_win_str_time,&temp_winroughdu);
	//initialize LogFileObj
	m_my_api.IntLogFileObj(m_hint_list,m_hwin_list,m_int_total,m_win_total,this,&m_privilage);
	//Load log
	if(m_my_api.LoadLog()==false)
	{//Cannot load the log file
		KillMeter();
		return;
	}

	if (m_privilage==SERVER)
	{//fresh start
	//Remove connection status file "Connected"
	m_my_api.SetStatusFile(DISCONNECTED);
	m_my_api.InitializeUserList();
	//Save windows start time
	m_my_api.GetTime(m_win_str_time);
	m_win_counter.Reset();
	}
	
	//At this point m_win_str_time can conver to seconds
	m_win_str_sec = m_my_api.ToSeconds(m_win_str_time);

	if (m_privilage==CLIENT)
	{
	//add current user to the registry
	m_my_api.AddUser();
	//Calculat win duration
	m_my_api.GetTime(m_now);
	m_my_api.TimeElapse(m_win_str_sec,m_now,m_temp_duration);
	//Set starting poit for win counter
	m_win_counter.SetAt(m_temp_duration,temp_winroughdu,true);
	//I am a client client timer tick faster for comunication efficiency
	SetTimer(TIMER_SERVER_LINK,500,0);
	}

	//Start main timer
	SetTimer(TIMER_MAIN,1000,0);
	SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_HIGH);
	//start hide timer
	SetTimer(TIMER_HIDE,200,0);
}
//------------------------------------------------------------------------------------------------
void CMainDlg::SetLable(int mode)
{
	if(m_select_tab == 1)
	{//Windows tab selected
		memcpy(m_res_label_text+96,m_win_duration,8);
		m_status_lbl.SetWindowText(m_res_label_text+86);
	}else{
	//Internet tab selected
		if(mode==ID_MODE_CONECT)
		{
			memcpy(m_res_label_text+49,m_int_duration,8);
			memcpy(m_res_label_text+76,m_int_total,9);
			m_status_lbl.SetWindowText(m_res_label_text+37);
		}else{
			memcpy(m_res_label_text+26,m_int_total,9);
			m_status_lbl.SetWindowText(m_res_label_text);
		}
	}
}
//------------------------------------------------------------------------------------------------
void CMainDlg::SetTip(int mode,int prayority)
{
static int count = 0;

	if(prayority!=ID_TIP_PRAYORITY_HIGH)
	{	if(count<5)
		{count++;
		return;}
	}
	count=0;

	if(mode==ID_MODE_CONECT)
	{
		memcpy(m_res_tip_text+96,m_win_duration,8);
		SetUpTray(NIM_MODIFY,m_res_tip_text+56,50);
	}else{
		SetUpTray(NIM_MODIFY,m_res_tip_text,55);
	}
}
//------------------------------------------------------------------------------------------------
void CMainDlg::TimerMain()
{
#ifdef _DEBUG
		bool		connected;
#else
		BOOL		connected;
#endif

static	bool		swap_dct = false;
		DAY_STRUCT	today;
		char		czprevi_day[3];
		DWORD		contype;
		bool		day_changed,month_changed;

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

	m_my_api.GetDay(&today,&day_changed,czprevi_day);
	month_changed	= m_my_api.DetectMonChange();
	m_my_api.GetTime(m_now);

	//Do Rough calculation of duration (For eficiency)
	m_win_counter.Incriment(m_win_duration);

if(m_privilage==SERVER)
{//++++++++++++++++++++++++++++++++++++ (IF SERVER) ++++++++++++++++++++++++++++++++++++++++++++
//DETECT CHANGE OF DAY
	if(day_changed)
	{
		if (contype==INTERNET_CONNECTION_MODEM)
		{//Save Internet log
			//m_my_api.TimeElapse(m_int_str_sec,m_now,m_temp_duration);
			m_int_counter.GetDuration(m_temp_rugh_dura);
			if(m_my_api.Save_Int_Usage(&today,m_int_str_time,m_now,m_temp_rugh_dura,m_temp_rugh_dura)==false)
			{
				KillMeter();
				return;
			}
			memcpy(m_int_str_time,m_now,9);
			m_int_str_sec=m_my_api.ToSeconds(m_int_str_time);
			m_int_counter.Reset();
		}
		//Save Windows log
		//m_my_api.TimeElapse(m_win_str_sec,m_now,m_temp_duration);
		m_win_counter.GetDuration(m_temp_rugh_dura);
		if(m_my_api.Save_Win_Usage(&today,m_win_str_time,m_now,m_temp_rugh_dura,m_temp_rugh_dura)==false)
			{
				KillMeter();
				return;
			}
		memcpy(m_win_str_time,m_now,9);
		m_win_str_sec=m_my_api.ToSeconds(m_win_str_time);
		m_win_counter.Reset();
	
		if (month_changed==false)
		{//If month has changed there is no need to load file because it loads in bellow month change check
		//load log file
			if(m_my_api.LoadLog()==false)
			{//Cannot load the log file
				KillMeter();
				return;
			}
		}
	}

	//DETECT CHANGE OF MONTH
	if (month_changed)
	{//Month shift
		m_my_api.MonthChange();
		//load log file
		if(m_my_api.LoadLog()==false)
		{//Cannot load the log file
			KillMeter();
			return;
		}
	}

//CHECK CONNECTION STATE
	if (contype==INTERNET_CONNECTION_MODEM)
	{
		if (swap_dct==false){
		swap_dct=true;
//-----------JUST CONNECTED----------------------
		memcpy(m_int_str_time,m_now,9);
		m_int_str_sec = m_my_api.ToSeconds(m_int_str_time);
		m_int_counter.Reset();
		SetTip(ID_MODE_CONECT,ID_TIP_PRAYORITY_HIGH);
		//Create "Connected" file to show connection state
		m_my_api.SetStatusFile(CONNECTED);
//-----------JUST CONNECTED-----------------------
		}
	}else{
		if (swap_dct==true){
		swap_dct=false;
//---------JUST DISCONNECTED----------------------
		//Save Internet log
		//m_my_api.TimeElapse(m_int_str_sec,m_now,m_temp_duration);
		m_int_counter.GetDuration(m_temp_rugh_dura);
		if(m_my_api.Save_Int_Usage(&today,m_int_str_time,m_now,m_temp_rugh_dura,m_temp_rugh_dura)==false)
		{
			KillMeter();
			return;
		}
		SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_HIGH);
		//Create "Disconnected" file to show connection state
		m_my_api.SetStatusFile(DISCONNECTED);
//---------JUST DISCONNECTED----------------------
		}}

//GIVE DATA AND ANSWER TO CLIENT IF NESSASARY
	m_my_api.SayServerActive(m_win_str_time,m_win_counter.m_duration_sec);

}else{
//+++++++++++++++++++++++++++++++++++++++ (IF CLIENT) ++++++++++++++++++++++++++++++++++++++++++

	//DETECT CHANGE OF DAY
	if(day_changed)
	{
		if (contype==INTERNET_CONNECTION_MODEM)
		{
		memcpy(m_int_str_time,m_now,9);
		m_int_str_sec=m_my_api.ToSeconds(m_int_str_time);
		m_int_counter.Reset();
		}

		memcpy(m_win_str_time,m_now,9);
		m_win_str_sec = m_my_api.ToSeconds(m_win_str_time);
		m_win_counter.Reset();

		if (month_changed==false)
		{//If month has changed there is no need to load file because it loads in bellow month change check
			//Wait untill server setup the log file
			::Sleep(1100);
			if(m_my_api.LoadLog()==false)
			{
				KillMeter();
				return;
			}
		}
	}
	//Detect month changed
	if (month_changed)
	{
		m_my_api.MonthChange();
		//Wait untill server setup the log file
		::Sleep(1100);
		if(m_my_api.LoadLog()==false)
		{
			KillMeter();
			return;
		}
	}

//CHECK CONNECTION STATE
	if (contype==INTERNET_CONNECTION_MODEM)
	{
		if (swap_dct==false){
		swap_dct=true;
//-----------JUST CONNECTED----------------------
		memcpy(m_int_str_time,m_now,9);
		m_int_str_sec=m_my_api.ToSeconds(m_int_str_time);
		m_int_counter.Reset();
		SetTip(ID_MODE_CONECT,ID_TIP_PRAYORITY_HIGH);
//-----------JUST CONNECTED----------------------
		}
	}else{
		if (swap_dct==true){
		swap_dct=false;
//---------JUST DISCONNECTED----------------------
		//Wait untill server setup file
		::Sleep(1100);
		if(m_my_api.LoadLog()==false)
		{
			KillMeter();
			return;
		}
		SetTip(ID_MODE_DESCONECT,ID_TIP_PRAYORITY_HIGH);
//---------JUST DISCONNECTED----------------------
		}}
}
//+++++++++++++++++++++++++++ (COMMON TO SERVER ANFD CLIENT) +++++++++++++++++++++++++++++++

//Setup Tip
	if (swap_dct==true){
	//Connected
	//Do Rough calculation of duration (For eficiency)
	m_int_counter.Incriment(m_int_duration);
	SetTip(ID_MODE_CONECT , ID_TIP_PRAYORITY_NORMAL);
	}else{
	//Disconnected
	SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_NORMAL);
	}
//Setup label
	if (!IsWindowVisible())
		return ;//Execut only if visible
	if (swap_dct==true){
	//Connected
	SetLable(ID_MODE_CONECT);
	}else{
	//Disconnected
	SetLable(ID_MODE_DESCONECT);
	}
}
//------------------------------------------------------------------------------------------------
void CMainDlg::OnFileViewer() 
{
char	path[_MAX_PATH];
DWORD	len = _MAX_PATH;
DWORD	last_slash;
STARTUPINFO si;
PROCESS_INFORMATION pi;

	//get app path
	GetAppPath(path,&len,false);
	//append "\\Viewer.exe" to the path
	last_slash = FindLatsSlash(path,len);
	memcpy(path+last_slash,"\\Viewer.exe\0",12);

	ZeroMemory(&si,sizeof(STARTUPINFO));
	//memset(&si,0,sizeof(STARTUPINFO));
	si.wShowWindow=1;
	si.cb=sizeof(STARTUPINFO);
	si.dwFlags=STARTF_USESTDHANDLES;

	if(CreateProcess(path,NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi)==0)
		::MessageBox(this->m_hWnd,"File Viewer cannot be load !    ","Usage Meter",MB_OK|MB_ICONEXCLAMATION);
}
//------------------------------------------------------------------------------------------------
void CMainDlg::GetAppPath(char* path,DWORD* len,bool writerunkey)
{
	//Get app path
	*len = GetModuleFileName(NULL,path,*len);

#ifdef _DEBUG
#else
	if(writerunkey==true)
	{//write Meter path to Run key
	SECURITY_ATTRIBUTES sa;
	HKEY hKey;
		sa.nLength=sizeof(sa);
		sa.bInheritHandle=1;
		sa.lpSecurityDescriptor=NULL;
		//Open or Create Key
		RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
		//Set Value
		RegSetValueEx(hKey,"UsageMeter",0,REG_SZ,(LPBYTE)path, *len);
		//Close
		RegCloseKey(hKey);
	}
#endif
}
//------------------------------------------------------------------------------------------------
DWORD CMainDlg::FindLatsSlash(char *path,DWORD len)
{
	for(DWORD i=len;i>0;i--)
	{
		if(path[i]=='\\')
			return i;
	}
	return 0;
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
//------------------------------------------------------------------------------------------------
void CMainDlg::OnBeepSet() 
{
CDlgBeepSetting	m_dlg_beep_set;
	m_dlg_beep_set.DoModal();
	SetBeep(m_dlg_beep_set.m_reset_int_count, m_dlg_beep_set.m_reset_win_count);
}
//------------------------------------------------------------------------------------------------
void CMainDlg::SetBeep(bool reset_int_count, bool reset_win_count)
{		
BEEP_STRUCT		ps;
	//Internet
	m_int_counter.RetriveSettings(&ps,false);
	m_int_counter.CheckInputs(&ps,false,NULL);
	m_int_counter.SetBeep(&ps,reset_int_count);
	//Windows
	m_win_counter.RetriveSettings(&ps,true);
	m_win_counter.CheckInputs(&ps,false,NULL);
	m_win_counter.SetBeep(&ps,reset_win_count);
}
//--------------------------------------------------------------------------------------------------------
void CMainDlg::KillMeter()
{
	::MessageBox(this->m_hWnd,"Cannot open the Log File, click Ok to close Usage Meter!     ","Usage Meter",MB_OK|MB_ICONSTOP);
	delete m_pop_menu;
	KillTimer(TIMER_SERVER_LINK);
	KillTimer(TIMER_MAIN);
	SetUpTray(NIM_DELETE,NULL,0);
	SaveWindowPos();
	m_my_api.RemoveUser();
	CDialog::EndDialog(0);
}
//--------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
void CMainDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_privilage==SERVER)
		AfxMessageBox("SERVER");
	else
		AfxMessageBox("CLIENT");
	CDialog::OnLButtonUp(nFlags, point);
}
//------------------------------------------------------------------------------------------------
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
