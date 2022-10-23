// MyMailWnd.cpp: implementation of the CMyMailWnd class.

#include "stdafx.h"
#include "resource.h"
#include "MyMainWnd.h"
#include "MyBeepDlg.h"
#include <shellapi.h>
#include <commctrl.h>
#include <Wininet.h>

CMyMainWnd::CMyMainWnd(){}
CMyMainWnd::~CMyMainWnd(){}
//--------------------------------------------------------------------------------------
void CMyMainWnd::SetUpWindow()
{
//****************** CTREATING WINDOWS ******************************************
	//System menue
	//Add about item to system menu
	HMENU hsys_menu = ::GetSystemMenu(m_hmain_window,FALSE);
	RemoveMenu(hsys_menu,2,MF_BYPOSITION);
	RemoveMenu(hsys_menu,2,MF_BYPOSITION);
	//EnableMenuItem(hsys_menu,2,MF_BYPOSITION|MF_GRAYED);
	RemoveMenu(hsys_menu,2,MF_BYPOSITION);
	RemoveMenu(hsys_menu,2,MF_BYPOSITION);
	RemoveMenu(hsys_menu,3,MF_BYPOSITION);
	RemoveMenu(hsys_menu,0,MF_BYPOSITION);
	AppendMenu(hsys_menu,MF_SEPARATOR,NULL,NULL);
	AppendMenu(hsys_menu,MF_STRING, ID_MENU_PERF,"Performance Data...");
	AppendMenu(hsys_menu,MF_SEPARATOR,NULL,NULL);
	AppendMenu(hsys_menu,MF_STRING, ID_MENU_ABOUT,"About Usage Meter...");
	//buttons
HWND hbut;
	hbut = CreateWindow("BUTTON","Ok",WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,430,490,70,24,m_hmain_window,(HMENU)ID_BUT_OK,m_hinstance,NULL );
	m_font_ok = CreateFont("Tahoma",6,13);
	SendMessage(hbut,WM_SETFONT,(WPARAM)m_font_ok,MAKELPARAM(FALSE, 0));
	hbut = CreateWindow("BUTTON","File Viewer",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON ,345,490,80,24,m_hmain_window,(HMENU)ID_BUT_FILEVIEW,m_hinstance,NULL );
	m_font_fview = CreateFont("Tahoma",6,13);
	SendMessage(hbut,WM_SETFONT,(WPARAM)m_font_fview,MAKELPARAM(FALSE, 0));
	hbut = CreateWindow("BUTTON","Beep...",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON ,260,490,80,24,m_hmain_window,(HMENU)ID_BUT_BEEP,m_hinstance,NULL );
	m_font_beep = CreateFont("Tahoma",6,13);
	SendMessage(hbut,WM_SETFONT,(WPARAM)m_font_beep,MAKELPARAM(FALSE, 0));
	//Lable
	m_hlable_ctrl	= CreateWindow("STATIC","Offline | Total - 000:00:00",WS_VISIBLE|WS_CHILD,10,494,250,24,m_hmain_window,(HMENU)ID_BUT_OK,m_hinstance,NULL );
	m_font_lable	= CreateFont("Tahoma",6,13);
	SendMessage(m_hlable_ctrl,WM_SETFONT,(WPARAM)m_font_lable,MAKELPARAM(FALSE, 0));
	//Tab control
	m_htab_ctrl = CreateWindow(WC_TABCONTROL,"MeterTab",WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE,5,5,501,480,m_hmain_window,(HMENU)ID_TAB_CTRL,m_hinstance,NULL); 
	m_font_tab	= CreateFont("Tahoma",6,13);
	SendMessage(m_htab_ctrl,WM_SETFONT,(WPARAM)m_font_tab,MAKELPARAM(FALSE, 0));
TCITEM ti;
	ti.mask = TCIF_TEXT ;ti.pszText = "Internet";ti.cchTextMax = 8;
	SendMessage(m_htab_ctrl,TCM_INSERTITEM,(WPARAM)1,(LPARAM)&ti);
	ti.pszText = "Windows";ti.cchTextMax = 7;
	SendMessage(m_htab_ctrl,TCM_INSERTITEM,(WPARAM)1,(LPARAM)&ti);
	//Static Frame
	hbut = CreateWindow("STATIC","",SS_BLACKFRAME|WS_VISIBLE|WS_CHILD,5,28,489,445,m_htab_ctrl,(HMENU)ID_BUT_OK,m_hinstance,NULL );
	//List views
	m_win_list.m_hlist = CreateWindow(WC_LISTVIEW,"MeterWinList",WS_BORDER|WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS,2,2,485,441,hbut,NULL,m_hinstance,NULL); 
	m_int_list.m_hlist = CreateWindow(WC_LISTVIEW,"MeterIntList",WS_BORDER|WS_VISIBLE|WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS,2,2,485,441,hbut,NULL,m_hinstance,NULL); 
	m_win_list.m_hfont = CreateFont("Verdana",7,13);
	m_int_list.m_hfont = CreateFont("Verdana",7,13);
	m_win_list.SetupListview();
	m_int_list.SetupListview();
//****************** CTREATING WINDOWS ******************************************
}
//--------------------------------------------------------------------------------------
void CMyMainWnd::TabChanged(LPARAM lParam)
{
NMHDR* nr = (NMHDR*)lParam;

	if(nr->code==TCN_SELCHANGE)
	{
		if(SendMessage(m_htab_ctrl,TCM_GETCURSEL,(WPARAM)0,(LPARAM)0)==0)
		{//Internet Tab
			m_select_tab = 0;
			ShowWindow(m_int_list.m_hlist,1);
			ShowWindow(m_win_list.m_hlist,0);
		}else{
			m_select_tab = 1;	
			ShowWindow(m_int_list.m_hlist,0);
			ShowWindow(m_win_list.m_hlist,1);
		}
	}
}
//--------------------------------------------------------------------------------------
HFONT CMyMainWnd::CreateFont(char* face,WORD len,WORD size)
{
LOGFONT lf;
HFONT	hfont;

	ZeroMemory(&lf,sizeof(LOGFONT));
	lf.lfHeight = size;
	memcpy(lf.lfFaceName,face,len);
	hfont = CreateFontIndirect(&lf);

	if(hfont==NULL)
		WriteLog("Unable to create font");

	return hfont;
}
//--------------------------------------------------------------------------------------
void CMyMainWnd::ShutDown(bool exit)
{
DWORD contype;
	//Remove Current User
	RemoveUser();
	//Kill Timers
	KillTimer(m_hmain_window,TIMER_MAIN);
	KillTimer(m_hmain_window,TIMER_COM);
	//Save Window Pos
	SaveWindowPos();
	DeleteFonts();

	if(exit==false)
	{//Nornal exit
		if(m_privilage==SERVER)
		{//Give privilage to running client to be a server
			if(GivePrivilage()==false)
			{//no clients to get privilage so I should save log
				//save windows usage
				Save_Win_Usage();
				//(save internet usage) This is only done if currently connected this connection will
				//terminate shortly after UsageMeter diminish this situation ocour when user log off
				//without disconnecting the internet
				if(InternetGetConnectedState(&contype, NULL))
				{
					if((contype&INTERNET_CONNECTION_MODEM)==INTERNET_CONNECTION_MODEM)
						Save_Int_Usage();
				}

				WriteLog("Server end");
			}else{
				WriteLog("Privilage Given");
			}
		}else{
			WriteLog("Client end");
		}
	}else{//Stopping UM by command line
		if(m_privilage==SERVER)
			WriteLog("Server end");
		else
			WriteLog("Client end");
	}

	//Release mutex
	CloseHandle(m_mutex);
	//Remove Tray icon
	SetUpTray(NIM_DELETE,NULL,0);
	//Clear dirty flag
	RegSet(HKEY_CURRENT_USER,"DirtyFlag",ID_DIRTY_FALSE);
	//Stop process
	PostQuitMessage(0);
}
//--------------------------------------------------------------------------------------
void CMyMainWnd::SetUpTray(DWORD Task,char* tip,int size)
{
NOTIFYICONDATA nd;
	nd.cbSize=sizeof(nd);
	nd.uCallbackMessage=ID_TRAY_ICON;
	nd.hIcon = LoadIcon(m_hinstance, (LPCTSTR)IDI_USAGEMETER);
	nd.hWnd = m_hmain_window;
	nd.uID = 1;
	nd.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	strncpy_s(nd.szTip, 64,tip ,size);

	if (Shell_NotifyIcon(Task, &nd)==0)
	{//Error lets reset icon
		Shell_NotifyIcon(NIM_DELETE, &nd);
		Shell_NotifyIcon(NIM_ADD, &nd);
		WriteLog("Tray icon reset");
	}
}
//--------------------------------------------------------------------------------------
void CMyMainWnd::StartUp()
{
	IntEventLog();

	//Create Font for exeption dlg box
	m_font_exep_edit = CreateFont("Courier New",11,15);

	//Set priority HIGH
	SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_HIGHEST);
	//Load resources
	//Fill m_res_tip_text buffer (Bit tricky)**********
	memcpy(m_res_tip_text,"Internet Usage : ###:##:##\n\rWindows running : 00:00:00\0",55);
	m_win_counter.m_duration.str_dura = m_res_tip_text + 46;//Directly send a part of buffer to counters (Efficiancy man Efficiancy...)
	m_int_total	= m_res_tip_text + 17;
	memcpy(m_res_tip_text+56,"Connected : 00:00:00\n\rWindows running : 00:00:00\0",49);
	m_int_counter.m_duration.str_dura = m_res_tip_text+68;
	//Fill m_res_label_text buffer
	memcpy(m_res_label_text,"Offline     |     Total - ###:##:##\0",36);
	memcpy(m_res_label_text+37,"Connected - 00:00:00     |     Total - ###:##:##\0",49);
	memcpy(m_res_label_text+86,"Running - 00:00:00     |     Total - ###:##:##\0",47);
	m_win_total	= m_res_label_text + 123;

	SetUpWindow();
	SetUpTray(NIM_ADD," Usage Meter \0",14);

	//Give reference to m_logthread_data ver
	m_logthread_data.pwin_list	= &m_win_list;
	m_logthread_data.pint_list	= &m_int_list;
	m_logthread_data.pum_log	= &m_um_log;
	m_logthread_data.pwin_total	= m_win_total;	
	m_logthread_data.pint_total	= m_int_total;

	m_pwin_counter	= &m_win_counter;
	m_pint_counter	= &m_int_counter;

	SetTime();//This func set the global "m_st" so must call befor other time related func
	SetDate();

DWORD df;
	RegGet(HKEY_CURRENT_USER,"DirtyFlag",&df);
	if(df==ID_DIRTY_TRUE)
	{//Dirty flag exist (Last shutdown is not proper)
		WriteLog("Last time Usage Meter was not properly shutdown");
	}else{
		RegSet(HKEY_CURRENT_USER,"DirtyFlag",ID_DIRTY_TRUE);
	}	

	if(LoadLog()==false)
	{
		WriteLog("Can not load the log file");
		KillMeter();
		return;
	}

	//check server running
	IsServerRunning();

	if (m_privilage==SERVER)
	{//fresh start
		AssosiateFiles();
		//User
		InitializeUserList();
		AddUser();
		//Get win start timr
		memcpy(m_win_str_time, m_now, 3);
		//Write log
		AddLine();
		WriteLog("Server started");
	}

	if (m_privilage==CLIENT)
	{
		//add current user to the registry
		AddUser();
		//Write log
		WriteLog("Client started");
	}

	SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_HIGH);

	SetTimer(m_hmain_window,TIMER_MAIN,1000,0);
	SetTimer(m_hmain_window,TIMER_COM,500,0);
}
//--------------------------------------------------------------------------------------
void CMyMainWnd::MainTimerTicks()
{
	if(m_skip_timer)
		return;

#ifdef _DEBUG
	bool		connected;
#else
	BOOL		connected;
#endif
//************* VARIABLES *******************
static	bool	swap_dct = false;
		DWORD	contype;
//************* VARIABLES *******************

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

	//Incriment Windows Counter
	m_win_counter.Increment();

	SetTime();
	QuarryDate();

if(m_privilage==SERVER)
{//++++++++++++++++++++++++++++++++++++ (IF SERVER) ++++++++++++++++++++++++++++++++++++++++++++
	//DETECT CHANGE OF DAY
	if(m_day_changed)
	{
		WriteLog("Day changed");
		if (contype==INTERNET_CONNECTION_MODEM)
		{//Save Internet log
			Save_Int_Usage();
			m_int_counter.Reset();
			memcpy(m_int_str_time, m_now, 3);
		}

		//Save Windows log
		Save_Win_Usage();
		m_win_counter.Reset();
		memcpy(m_win_str_time, m_now, 3);

		//Update m_pre_day ver( After saving logs)
		UpdateDate();

		if (m_month_changed==false)
		{//If month has changed there is no need to load file 
			//because it loads in bellow month change check
			LoadLog();
		}
	}

	//DETECT CHANGE OF MONTH
	if (m_month_changed)
	{//load log file
		WriteLog("Month changed");
		LoadLog();
	}

	//CHECK CONNECTION STATE
	if (contype==INTERNET_CONNECTION_MODEM)
	{
		if (swap_dct==false){
			swap_dct=true;
//-----------JUST CONNECTED-----------------------
			WriteLog("Connected");
			m_int_counter.Reset();
			memcpy(m_int_str_time,m_now,3);
			SetTip(ID_MODE_CONECT,ID_TIP_PRAYORITY_HIGH);
//-----------JUST CONNECTED-----------------------
		}
	}else{
		if (swap_dct==true)
		{
			swap_dct=false;
//---------JUST DISCONNECTED----------------------
			WriteLog("Disconnected");
			Save_Int_Usage();
			LoadLog();
			SetTip(ID_MODE_DESCONECT,ID_TIP_PRAYORITY_HIGH);
//---------JUST DISCONNECTED----------------------
		}
	}

	//GIVE DATA AND ANSWER TO CLIENT IF NESSASARY
	SayServerActive();

}else{
//+++++++++++++++++++++++++++++++++++++++ (IF CLIENT) ++++++++++++++++++++++++++++++++++++++++++
	//DETECT CHANGE OF DAY
	if(m_day_changed)
	{
		if (contype==INTERNET_CONNECTION_MODEM)
		{
			m_int_counter.Reset();
			memcpy(m_int_str_time, m_now, 3);
		}

		m_win_counter.Reset();
		memcpy(m_win_str_time, m_now, 3);

		if (m_month_changed==false)
		{//If month has changed there is no need to load file because it loads in bellow month change check
			//Wait untill server setup the log file
			Sleep(1100);
			LoadLog();
		}
	}
	//Detect month changed
	if (m_month_changed)
	{
		//Wait untill server setup the log file
		Sleep(1100);
		LoadLog();
	}

//CHECK CONNECTION STATE
	if (contype==INTERNET_CONNECTION_MODEM)
	{
		if (swap_dct==false){
		swap_dct=true;
//-----------------JUST CONNECTED--------------------------
		m_int_counter.Reset();
		memcpy(m_int_str_time,m_now,3);
		SetTip(ID_MODE_CONECT,ID_TIP_PRAYORITY_HIGH);
//----------------JUST CONNECTED---------------------------
		}
	}else{
		if (swap_dct==true){
		swap_dct=false;
//--------------JUST DISCONNECTED--------------------------
		//Wait untill server setup file
		Sleep(1100);
		LoadLog();
		
		SetTip(ID_MODE_DESCONECT,ID_TIP_PRAYORITY_HIGH);
//--------------JUST DISCONNECTED--------------------------
		}
	}
}

//+++++++++++++++++++++++++++ (COMMON TO SERVER AND CLIENT) +++++++++++++++++++++++++++++++

//****************Setup Tip*********************************
	if (swap_dct==true){
	//Connected
	m_int_counter.Increment();
	SetTip(ID_MODE_CONECT , ID_TIP_PRAYORITY_NORMAL);
	}else{
	//Disconnected
	SetTip(ID_MODE_DESCONECT , ID_TIP_PRAYORITY_NORMAL);
	}
//*****************Setup label******************************

	if (!IsWindowVisible(m_hmain_window))
		return ;//Execut only if visible
	if (swap_dct==true){
	//Connected
	SetLable(ID_MODE_CONECT);
	}else{
	//Disconnected
	SetLable(ID_MODE_DESCONECT);
	}
}
//--------------------------------------------------------------------------------------
void CMyMainWnd::SetLable(int mode)
{
	if(m_select_tab == 1) 
	{//Windows tab selected
		memcpy(m_res_label_text+96,m_win_counter.m_duration.str_dura,8);
		SendMessage(m_hlable_ctrl,WM_SETTEXT,(WPARAM)0,(LPARAM)(LPCTSTR)m_res_label_text+86);
	}else{
	//Internet tab selected
		if(mode==ID_MODE_CONECT)
		{
			memcpy(m_res_label_text+49,m_int_counter.m_duration.str_dura,8);
			memcpy(m_res_label_text+76,m_int_total,9);
			SendMessage(m_hlable_ctrl,WM_SETTEXT,(WPARAM)0,(LPARAM)(LPCTSTR)m_res_label_text+37);
		}else{
			memcpy(m_res_label_text+26,m_int_total,9);
			SendMessage(m_hlable_ctrl,WM_SETTEXT,(WPARAM)0,(LPARAM)(LPCTSTR)m_res_label_text);
		}
	}
}
//------------------------------------------------------------------------------------------------
void CMyMainWnd::SetTip(int mode,int prayority)
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
		memcpy(m_res_tip_text+96,m_win_counter.m_duration.str_dura,8);
		SetUpTray(NIM_MODIFY,m_res_tip_text+56,50);
	}else{
		SetUpTray(NIM_MODIFY,m_res_tip_text,55);
	}
}
//------------------------------------------------------------------------------------------------
void CMyMainWnd::ComTimerTicks()
{//For commiunication perpose
	//chek weather a server given privilage
	if (m_privilage==CLIENT)
		GrantPrivilages();

	//Check for Command Line commands
DWORD answer;
	RegGet(HKEY_LOCAL_MACHINE,"ComPort",&answer);

	switch(answer)
	{
		case MSG_EXIT_UM:
			//Invalidate ComPort
			if (m_privilage==SERVER)
				RegSet(HKEY_LOCAL_MACHINE,"ComPort",MSG_INVALID);
			ShutDown(true);
		break;
		case MSG_START_VIEWER:
			//Invalidate ComPort
			if (m_privilage==SERVER)
				RegSet(HKEY_LOCAL_MACHINE,"ComPort",MSG_INVALID);
			LaunchViewer();
		break;
	}
}
//------------------------------------------------------------------------------------------------
void CMyMainWnd::KillMeter()
{
	KillTimer(m_hmain_window,TIMER_MAIN);
	KillTimer(m_hmain_window,TIMER_COM);
	DeleteFonts();

	SetUpTray(NIM_DELETE,NULL,0);
	DestroyWindow(m_hmain_window);
}
//------------------------------------------------------------------------------------------------
void CMyMainWnd::SaveWindowPos()
{
RECT dlg_rect;
	//Save pos
	GetWindowRect(m_hmain_window, &dlg_rect);
	RegSet(HKEY_CURRENT_USER,"x",dlg_rect.left);
	RegSet(HKEY_CURRENT_USER,"y",dlg_rect.top);
}
//-------------------------------------------------------------------------------------------
void CMyMainWnd::DeleteFonts()
{
	//Deleting Fonts  
	DeleteObject(m_font_tab);
	DeleteObject(m_font_ok);
	DeleteObject(m_font_fview);
	DeleteObject(m_font_beep);
	DeleteObject(m_font_lable);
	DeleteObject(m_font_exep_edit);
}
//------------------------------------------------------------------------------------------------
void CMyMainWnd::LaunchViewer()
{
PROCESS_INFORMATION pi;
STARTUPINFO			si;
DWORD				len;
char				path[_MAX_PATH];

	len = _MAX_PATH;
	RegGet(HKEY_LOCAL_MACHINE,"WorkingDir",path,_MAX_PATH,&len);
	len -= 2;
	memcpy(&path[len],"\\Viewer.exe\0",12);

	ZeroMemory(&si,sizeof(STARTUPINFO));
	si.cb			= sizeof(STARTUPINFO);
	si.dwFlags		= STARTF_USESTDHANDLES;
	si.wShowWindow	= 1;

	if(CreateProcess(path,NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi)==0)
		MessageBox(NULL,"File Viewer cannot be load!  ","Usage Meter",MB_OK|MB_ICONEXCLAMATION);
}
//------------------------------------------------------------------------------------------------
/*BYTE CMyMainWnd::CheckPointers()
{
BOOL r = TRUE;

	r = IsBadStringPtr(m_win_counter.m_duration.str_dura,1);
	r = IsBadStringPtr(m_int_counter.m_duration.str_dura,1);
	r = IsBadStringPtr(m_int_total,1);
	r = IsBadStringPtr(m_win_total,1);
	r = IsBadStringPtr(m_logthread_data.pwin_total,1);
	r = IsBadStringPtr(m_logthread_data.pint_total,1);

	if(r==TRUE)
	{
		WriteLog("Error - Bad pointer");
		Beep(2000,100);
		return 0;
	}else{
		return 1;
	}
}*/
//------------------------------------------------------------------------------------------------
#ifdef _DEBUG
bool CMyMainWnd::Fake_Connection()
{
DWORD i;

	RegGet(HKEY_LOCAL_MACHINE,"Connected",&i);

	if(i==1)
		return true;
	return false;
}
#endif

