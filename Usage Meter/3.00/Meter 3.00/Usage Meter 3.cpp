// Usage Meter 3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "MyLogFile.h"	
#include "MyMainWnd.h"
#include "MyBeepDlg.h"
#include <stdio.h>


#define MAX_LOADSTRING 100

CMyBeepDlg	Beep_Dlg;
CMyMainWnd	Main_Window;
HINSTANCE	g_hInstance;
HWND		g_hAbout_dlg;
HWND		g_ex_edit;
HMENU		hpop;
HBRUSH		hdlgbrush;
long		old_edit_prog;
char		g_exit[5];
BYTE		g_i = 0;

LRESULT CALLBACK	TipWindow(HWND hEdit, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	BeepEditProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	GetPathDlg(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ExeptionDlg(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	PerformanceDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK	BeepDlg(HWND, UINT, WPARAM, LPARAM);
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LONG				FloatExeption(LPVOID lpThreadData);
LONG				FillList(LPVOID lpThreadData);
void				FormatTotal(char *buf, DWORD* seconds);
void				ShowAboutBox();
void				MakePopMenu();
//--------------------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
MSG msg;

try
{
#ifdef _DEBUG
#else
	//Check wether a previous instance running
	Main_Window.m_mutex = CreateMutex(NULL,TRUE,"UsageMeter3.00Mutex");
	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
	DWORD wh;
		CloseHandle(Main_Window.m_mutex);
		Main_Window.RegGet(HKEY_CURRENT_USER,"WinHandle",&wh);
		ShowWindow((HWND)wh,1);
		SetForegroundWindow((HWND)wh);
		return FALSE;
	}
#endif

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
		return FALSE;

	g_hAbout_dlg = 0;
	g_ex_edit	 = 0;

	Main_Window.StartUp();

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}catch(...){
	Beep(2000,10);
	Main_Window.WriteLog("Critical error");
	MessageBox(NULL,"Critical error!   ","Usage Meter",MB_OK|MB_ICONEXCLAMATION);
}
	return msg.wParam;
}
//##################################### CALL BACKS ###########################################
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
int wmId, wmEvent;

	switch (message) 
	{ 
	case WM_TIMER://+++MSG+++
	//Timer
		switch (wParam) 
		{ 
			case TIMER_MAIN:
				Main_Window.MainTimerTicks();
			break;
			case TIMER_SERVER_LINK:
				Main_Window.ServerTimerTicks();
			break;
			case TIMER_EXIT:
				g_i = 0;
				if(memcmp(g_exit,"exit",4)==0)
				{
					g_exit[0] = g_exit[1] = g_exit[2] = g_exit[3] = 'f';
					if(MessageBox(NULL,"ShutDown UM?  ","Usage Meter",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
					{
						Main_Window.ShutDown();
						PostQuitMessage(0);
						return 0;
					}
				}
			break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
	break;
	case ID_TRAY_ICON://+++MSG+++
	//Tray icon Msg
		if(lParam==WM_LBUTTONDOWN)
		{//LBUTTON DOWN
			ShowWindow(hWnd,1);
			SetForegroundWindow(hWnd);
			return 0;
		}
		if(lParam==WM_RBUTTONDOWN)
		{//RBUTTON DOWN
			SetForegroundWindow(hWnd);
			MakePopMenu();
			return 0;
		}
	break;
	case WM_COMMAND://+++MSG+++
	HANDLE th;
		switch (wParam) 
			{ 
				case ID_BUT_FILEVIEW:
					Main_Window.LaunchViewer();
					break;
				case ID_BUT_BEEP: 
					DialogBox(g_hInstance,(LPCTSTR)IDD_BEEP_DLG,Main_Window.m_hmain_window,(DLGPROC)BeepDlg);
					break;		
				case ID_BUT_OK:
					ShowWindow(hWnd,0);
				break;
				case ID_MENU_ABOUT:
					ShowAboutBox();
				break;
				case ID_MENU_SHOWHIDE:
					if(IsWindowVisible(Main_Window.m_hmain_window))
						ShowWindow(Main_Window.m_hmain_window,0);
					else
						ShowWindow(Main_Window.m_hmain_window,1);
				break;
				case ID_FILL_LIST:
					th = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)FillList,(LPVOID)lParam,CREATE_SUSPENDED ,NULL);
					SetThreadPriority(th,THREAD_PRIORITY_IDLE);
					ResumeThread(th); 
				break;
				case ID_SHOW_EXEPTION:
					return DialogBox(g_hInstance,(LPCTSTR)IDD_EXCEPTION_DLG,Main_Window.m_hmain_window,(DLGPROC)ExeptionDlg);
				break;
				case ID_SHOW_FLOAT_EXEP:
					if(g_ex_edit==0)
						CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)FloatExeption,(LPVOID)lParam,0,NULL);
					else
						SetWindowText(g_ex_edit,Main_Window.m_ex.list_ex);
				break;
				case ID_SHOW_PATH_DLG:
					return DialogBox(g_hInstance,(LPCTSTR)IDD_GETPATHBOX,Main_Window.m_hmain_window,(DLGPROC)GetPathDlg);
				break;		
				default:
					 return DefWindowProc(hWnd, message, wParam, lParam);
			}
	break;
	case WM_NOTIFY://+++MSG+++
		if(ID_TAB_CTRL==wParam)
				Main_Window.TabChanged(lParam);
	break;
	case WM_SYSCOMMAND://+++MSG+++
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
				
		switch (wmId)
		{
			case ID_MENU_PERF:
				CreateDialog(g_hInstance,(LPCTSTR)IDD_PERF_DATA,Main_Window.m_hmain_window,(DLGPROC)PerformanceDlg);
			break;
			case ID_MENU_ABOUT:
				ShowAboutBox();
			break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
	break;
	case WM_DESTROY://+++MSG+++
		PostQuitMessage(0);
	break;
	case WM_CLOSE://+++MSG+++
			#ifdef _DEBUG
			Main_Window.ShutDown();
			PostQuitMessage(0);
			#else
			ShowWindow(hWnd,0);
			#endif
	break;
	case WM_KEYDOWN://+++MSG+++
		if(wParam==VK_ESCAPE)//Esc key press
			ShowWindow(hWnd,0);
		return 0;
	break;
	case WM_ENDSESSION://+++MSG+++
		Main_Window.ShutDown();
		PostQuitMessage(0);
		return 0;
	break;
	/*case WM_RBUTTONDOWN://+++MSG+++
		if(Main_Window.m_privilage==CLIENT)
			Beep(100,10);
	break;*/
	case WM_CHAR:
		g_exit[g_i] = (TCHAR)wParam;
		g_i++;
	break;
	default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
   return 0;
}
//--------------------------------------------------------------------------------------
LRESULT CALLBACK GetPathDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
RECT	rc;
	switch (message)
	{
		case WM_INITDIALOG:
			//Centre dlg box
			GetWindowRect(GetDesktopWindow(),&rc);
			MoveWindow(hDlg,(rc.right-472)/2,(rc.bottom-130)/2,472,130,FALSE);
			return TRUE;
		
		case WM_COMMAND:
			if (LOWORD(wParam)==IDC_BUTTON_CALCEL) 
			{
				//Main_Window.AddExeption("User refused to enter the log path!");
				EndDialog(hDlg, LOWORD(0));
				return TRUE;
			}
			if(LOWORD(wParam)==IDC_BUTTON_OK)
			{//************* IDC_BUTTON_OK **************************************************
			WIN32_FIND_DATA fd;
			HANDLE			hfind;
			DWORD			l;
			char			path[MAX_PATH];
							
				l = GetWindowText(GetDlgItem(hDlg,IDC_EDIT_PATH),path,MAX_PATH);

				if(l==0)
				{//Empty text box
					MessageBox(hDlg, "Please enter the path!      ", "Usage Meter", MB_OK | MB_ICONINFORMATION);
					return TRUE;
				}

				//**************************************
				if(path[l-1]=='\\')
				{//Like "c:\"
					memcpy(&path[l],"*\0",2);
				}else{//Like "c:\Log"
					memcpy(&path[l],"\\*\0",3);
					l += 1;
				}
				//Check wether the folder is exist
				hfind = FindFirstFile(path, &fd);
				FindClose(hfind);
				//Remove *
				path[l] = '\0';
				//**************************************

				if((hfind==INVALID_HANDLE_VALUE))
				{//Nop! folder is not there, so prompt for a new path
					MessageBox(hDlg, "Cannot locate the specified Folder!    ", "Usage Meter", MB_OK | MB_ICONEXCLAMATION);
					return TRUE;
				}

				//Write path to the registry
				Main_Window.m_ex.err = false;
				Main_Window.RegSet(HKEY_LOCAL_MACHINE,"LogFolder",path,l);
				if(Main_Window.m_ex.err)
				{
					//Main_Window.AddExeption("Cannot save Log Path!");
					EndDialog(hDlg, LOWORD(0));
				}
				else
				{
					EndDialog(hDlg, LOWORD(ID_SET_PATH));
				}
				
				return TRUE;
			}//************* IDC_BUTTON_OK *************************************************
		break;
	}
    return FALSE;
}
//-------------------------------------------------------------------------------------------
LRESULT CALLBACK ExeptionDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
RECT	rc;
switch (message)
	{
		case WM_INITDIALOG:
			//Set fonts
			g_ex_edit = CreateWindow("EDIT",Main_Window.m_ex.list_ex,WS_BORDER|ES_READONLY|WS_VISIBLE|WS_CHILD|WS_VSCROLL |ES_AUTOVSCROLL|ES_MULTILINE  ,3,3,460,130,hDlg,(HMENU)ID_BUT_OK,g_hInstance,NULL );
			SendMessage(g_ex_edit,WM_SETFONT,(WPARAM)Main_Window.m_font_exep_edit,MAKELPARAM(FALSE, 0));
			//Centre dlg box
			GetWindowRect(GetDesktopWindow(),&rc);
			MoveWindow(hDlg,(rc.right-472)/2,(rc.bottom-195)/2,472,195,FALSE);
			return TRUE;
		break;
		case WM_COMMAND:
			if (LOWORD(wParam)==IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
		break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return 0;
		break;
		case WM_DESTROY:
			g_ex_edit = 0;
		break;
	}
    return FALSE;
}
//--------------------------------------------------------------------------------------
LRESULT CALLBACK PerformanceDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			SetTimer(hDlg,TIMER_PERFORMANCE,1000,0);
			ShowWindow(hDlg,1);
			break;
		case WM_KEYDOWN:
			if (VK_ESCAPE == (int)wParam) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
		break;			
		case WM_CLOSE:
			KillTimer(hDlg,TIMER_PERFORMANCE);
			EndDialog(hDlg, LOWORD(wParam));
			return 0;
		break;
		case WM_TIMER:
		DWORD			d1,d2;
		HANDLE			hp;
		FILETIME		kt,ut,et,ct;
		SYSTEMTIME		st;
		MEMORYSTATUS	memst;
		char			output[15];
			//Handle
			hp = GetCurrentProcess();
			//Times**********************************
			GetProcessTimes(hp,&ct,&et,&kt,&ut);
			//Kernal
			FileTimeToSystemTime(&kt,&st);
			//st.wHour			= 1;st.wMinute			= 32;st.wSecond			= 20;st.wMilliseconds	= 100;
			d1 = (st.wMinute*60000) + (st.wSecond*1000) + st.wMilliseconds;
			wsprintf(output," Kernel - %i ms",d1);
			SetWindowText(GetDlgItem(hDlg,IDC_STATIC_KER),output);
			//User
			FileTimeToSystemTime(&ut,&st);
			d2 = (st.wMinute*60000) + (st.wSecond*1000) + st.wMilliseconds;
			wsprintf(output," User - %i ms",d2);
			SetWindowText(GetDlgItem(hDlg,IDC_STATIC_USER),output);
			//Total
			d1 = d1 + d2;
			wsprintf(output," Total - %i ms",d1);
			SetWindowText(GetDlgItem(hDlg,IDC_STATIC_TOT),output);

			//Memory*********************************
			GlobalMemoryStatus(&memst);
			wsprintf(output,"Used - %i %%",memst.dwMemoryLoad);
			SetWindowText(GetDlgItem(hDlg,IDC_STATIC_USED),output);

			memst.dwAvailPhys = memst.dwAvailPhys/1048576;
			wsprintf(output,"Free - %i MB",memst.dwAvailPhys);
			SetWindowText(GetDlgItem(hDlg,IDC_STATIC_AVAI),output);

			memst.dwTotalPhys = memst.dwTotalPhys/1048576;
			wsprintf(output,"Tatal - %i MB",memst.dwTotalPhys);
			SetWindowText(GetDlgItem(hDlg,IDC_STATIC_TOTAL),output);
		break;
	}
    return FALSE;
}
//--------------------------------------------------------------------------------------
LRESULT CALLBACK BeepDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			//Possison Dlg
		RECT rc;
			GetWindowRect(Main_Window.m_hmain_window,&rc);
			MoveWindow(hDlg,rc.left+150,rc.top+300,264,155,false);
			Beep_Dlg.Initialize(&Main_Window.m_win_counter.m_beep,&Main_Window.m_int_counter.m_beep,hDlg);
			Beep_Dlg.StartUp();
			//Sub class Edit controls WndProg (impliment Max len restriction)
			old_edit_prog = SetWindowLong(GetDlgItem(hDlg,EDIT_WIN_FREE),GWL_WNDPROC,(long)BeepEditProc);
							SetWindowLong(GetDlgItem(hDlg,EDIT_WIN__DUR),GWL_WNDPROC,(long)BeepEditProc);
							SetWindowLong(GetDlgItem(hDlg,EDIT_WIN_INTER),GWL_WNDPROC,(long)BeepEditProc);
							SetWindowLong(GetDlgItem(hDlg,EDIT_INT_FREE),GWL_WNDPROC,(long)BeepEditProc);
							SetWindowLong(GetDlgItem(hDlg,EDIT_INT_DUR),GWL_WNDPROC,(long)BeepEditProc);
							SetWindowLong(GetDlgItem(hDlg,EDIT_INT_INTER),GWL_WNDPROC,(long)BeepEditProc);
			break;
		case WM_NOTIFY:
		if(IDC_TAB_BEEP==wParam)
				Beep_Dlg.TabChanged(lParam);
			break;
		case WM_LBUTTONDOWN:
		POINT spt,cpt;
			GetCursorPos(&spt);
			cpt.x=spt.x;cpt.y=spt.y;
			ScreenToClient(hDlg,&cpt);
			if(cpt.x>235)
			{
				if(cpt.y<22)
				{
				WNDCLASSEX wcex;
					wcex.cbSize = sizeof(WNDCLASSEX); 
					wcex.style			= CS_HREDRAW | CS_VREDRAW;
					wcex.lpfnWndProc	= (WNDPROC)TipWindow;
					wcex.cbClsExtra		= 0;
					wcex.cbWndExtra		= 0;
					wcex.hInstance		= g_hInstance;
					wcex.hIcon			= NULL;
					wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
					wcex.hbrBackground	= CreateSolidBrush(RGB(255,255,225));
					wcex.lpszMenuName	= NULL;
					wcex.lpszClassName	= "MeterTip";
					wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
					RegisterClassEx(&wcex);
					CreateWindowEx(WS_EX_NOPARENTNOTIFY|WS_EX_TOPMOST|WS_EX_WINDOWEDGE,"MeterTip","Usage Meter",WS_VISIBLE|WS_POPUP|WS_BORDER,spt.x-100,spt.y,200,80,hDlg,NULL,g_hInstance,NULL);
				}
			}
			break;
		case WM_DESTROY:
			break;
		case WM_COMMAND:
				switch (LOWORD(wParam))
				{
				case IDOK:
					if(Beep_Dlg.SaveBeep())
						EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				break;

				case IDCANCEL: 
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				break;

				case IDC_TEST_BEEP:
					Beep_Dlg.TestBeep();
				break;
				}
		break;
	}
    return FALSE;
}
//--------------------------------------------------------------------------------------
LRESULT CALLBACK TipWindow(HWND hTip, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_ACTIVATE:
			if(LOWORD(wParam)==WA_INACTIVE)
			{
				SetFocus(Main_Window.m_hmain_window);
				DestroyWindow(hTip);
			}
		break;
	}


	return DefWindowProc(hTip, message, wParam, lParam);
}
//--------------------------------------------------------------------------------------
LRESULT CALLBACK BeepEditProc(HWND hEdit, UINT message, WPARAM wParam, LPARAM lParam)
{//SET MAX LEN OF TEXT BOXES
if(message==WM_CHAR)
{
long	r;
char	c1[6],c2[6];

		GetWindowText(hEdit,c1,6);	
		
		r = CallWindowProc((WNDPROC)old_edit_prog,hEdit,message,wParam,lParam);

		if(GetWindowText(hEdit,c2,6)==5)
		{
			SetWindowText(hEdit,c1);
			Beep(800,20);
		}
	return r;
}
	return CallWindowProc((WNDPROC)old_edit_prog,hEdit,message,wParam,lParam);
}
//--------------------------------------------------------------------------------------
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
		RECT wr;
			g_hAbout_dlg = hDlg;
			GetWindowRect(hDlg,&wr);
			MoveWindow(hDlg,wr.left,wr.top,368,266,false);
			return TRUE;
		case WM_DESTROY:
			g_hAbout_dlg = 0;
		break;
		case WM_LBUTTONDOWN:
			ReleaseCapture();
			SendMessage(hDlg,WM_NCLBUTTONDOWN,HTCAPTION,lParam);
		break;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
		break;
	}
    return FALSE;
}
//----------------------------------------------------------------------------------------
LONG FillList(LPVOID lpThreadData)
{
MY_LOG_THREAD_DATA* pthread_data;
char				username[MAX_PATH];
DWORD				slen;
DWORD				wintot,inttot,i;

	pthread_data = (MY_LOG_THREAD_DATA*)lpThreadData;
	slen = 16;
	wintot = inttot =0;

	pthread_data->pwin_list->DeleteAll();
	pthread_data->pint_list->DeleteAll();

	//Decrypt
	for(i=0;i<=pthread_data->len;i++)
		pthread_data->data[i] = pthread_data->data[i]^130;

	i = 0;
	pthread_data->pwin_list->count = 0;
	pthread_data->pwin_list->DrawList(FALSE);
	pthread_data->pint_list->count = 0;
	pthread_data->pint_list->DrawList(FALSE);
		
	do
	{
		//Fill structure
		memcpy(pthread_data->pum_log, &pthread_data->data[i], slen);
		i += slen;
		//Get user name
		memcpy(&username, &pthread_data->data[i], pthread_data->pum_log->users_len);
		i += pthread_data->pum_log->users_len;
		pthread_data->pum_log->users = username;
		//Fill list
		if(pthread_data->pum_log->type==ID_WIN_LOG)
		{
			pthread_data->pwin_list->InsertRow(pthread_data->pum_log);
			wintot += (pthread_data->pum_log->duration[0]*3600) + (pthread_data->pum_log->duration[1]*60) + pthread_data->pum_log->duration[2];
		}else{
			pthread_data->pint_list->InsertRow(pthread_data->pum_log);
			inttot += (pthread_data->pum_log->duration[0]*3600) + (pthread_data->pum_log->duration[1]*60) + pthread_data->pum_log->duration[2];
		}
	}while(i!=pthread_data->len);

	//Set total
	FormatTotal(pthread_data->pwin_total, &wintot);
	FormatTotal(pthread_data->pint_total, &inttot);

	//Finalize
	pthread_data->pwin_list->DrawList(TRUE);
	pthread_data->pint_list->DrawList(TRUE);

	delete[] pthread_data->data;
	CloseHandle(pthread_data->hlogfile);
	return 0;
}
//----------------------------------------------------------------------------------------
LONG FloatExeption(LPVOID lpThreadData)
{
	DialogBox(g_hInstance,(LPCTSTR)IDD_EXCEPTION_DLG,NULL,(DLGPROC)ExeptionDlg);
	//MessageBox(NULL, (char*)lpThreadData, "Usage Meter", MB_OK | MB_ICONEXCLAMATION);
	delete[] lpThreadData;
	return 0;
}
//##################################### CALL BACKS ###########################################

//######################################## TRASH #############################################
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_USAGEMETER3);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_BTNFACE+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "MeterWindow";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}
//--------------------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
HWND hWnd;
DWORD	x,y;
	g_hInstance = hInstance;
	hWnd = CreateWindow("MeterWindow","Usage Meter", 
	WS_OVERLAPPEDWINDOW,
	250,100,515,552,GetDesktopWindow(),NULL,hInstance,NULL);

	if (!hWnd)
		return FALSE;
	//Posision Main Dlg
	x = y = 0;
	Main_Window.RegGet(HKEY_CURRENT_USER,"x",&x);
	Main_Window.RegGet(HKEY_CURRENT_USER,"y",&y);
	if (x==0||y==0){ x=100 ;y=100;}
		SetWindowPos(hWnd,NULL,x,y,0,0,SWP_NOSIZE|SWP_NOOWNERZORDER);
	
	Main_Window.RegSet(HKEY_CURRENT_USER,"WinHandle",(DWORD)hWnd);
	Main_Window.m_hinstance		= hInstance;
	Main_Window.m_hmain_window	= hWnd;
	return TRUE;
}
//--------------------------------------------------------------------------------------
void ShowAboutBox()
{
	if(g_hAbout_dlg==0)
		DialogBox(g_hInstance,(LPCTSTR)IDD_ABOUTBOX,Main_Window.m_hmain_window,(DLGPROC)About);
	else
		SetForegroundWindow(g_hAbout_dlg);
}
//--------------------------------------------------------------------------------------
void MakePopMenu()
{
MENUITEMINFO	ms;
POINT			cp;

	ZeroMemory(&ms,sizeof(ms));
	ms.cbSize = sizeof(ms);

	hpop = CreatePopupMenu();
	//Show Hide
	ms.fType	= MFT_STRING;
	ms.fMask	= MIIM_DATA|MIIM_ID|MIIM_TYPE|MIIM_STATE;
	ms.fState	= MFS_DEFAULT;
	ms.wID		= ID_MENU_SHOWHIDE;
	if(IsWindowVisible(Main_Window.m_hmain_window))
	{
		ms.dwTypeData = "Hide";
		ms.cch = 5;
	}else{
		ms.dwTypeData = "Show";
		ms.cch = 5;
	}
	InsertMenuItem(hpop,0,FALSE,&ms);
	//File viewer
	ms.fType	= MFT_STRING;
	ms.fMask	= MIIM_DATA|MIIM_ID|MIIM_TYPE;
	ms.wID		= ID_BUT_FILEVIEW;
	ms.dwTypeData = "File Viewer...";
	ms.cch = 15;
	InsertMenuItem(hpop,0,FALSE,&ms);
	//Separator
	ms.fType	= MFT_SEPARATOR;
	ms.fMask	= MIIM_TYPE;
	InsertMenuItem(hpop,1,FALSE,&ms);
	//About
	ms.fType	= MFT_STRING;
	ms.fMask	= MIIM_DATA|MIIM_ID|MIIM_TYPE;
	ms.dwTypeData = "About...";
	ms.cch = 9;
	ms.wID		= ID_MENU_ABOUT;
	InsertMenuItem(hpop,2,FALSE,&ms);

	GetCursorPos(&cp);
	TrackPopupMenu(hpop,TPM_LEFTALIGN|TPM_RIGHTBUTTON,cp.x,cp.y,0,Main_Window.m_hmain_window,NULL);
	DestroyMenu(hpop);
}
//----------------------------------------------------------------------------------------
void FormatTotal(char *buf, DWORD* seconds)
{//Capacity <999:59:59
DWORD num,single,divid,index,d[3];
	
	buf[3] = buf[6] = ':';

//Convert seconds to time
	d[0]		= *seconds/3600;//Hourse
	*seconds	= *seconds%3600;//Reminder
	d[1]		= *seconds/60;	//Minutes
	d[2]		= *seconds%60;	//Reminder(That's seconds)

for(int t=0;t<=2;t++)
{//Loop through three time components
	//Get each components
	num = d[t];

	if(t==0)
	{//Hour part can be > 59 so deferent algo
		for(int i=0;i<=2;i++)
		{
			switch (i)
			{
			case 0:
				divid=100;
				single = num/divid;
				break;
			case 1:
				divid=10;
				num = single;
				single = num/divid;
				break;
			}

			switch (single)
			{
			case 0:
				buf[i]='0';single = num;break;
			case 1:
				buf[i]='1';single=num-1*divid;break;
			case 2:
				buf[i]='2';single=num-2*divid;break;
			case 3:
				buf[i]='3';single=num-3*divid;break;
			case 4:
				buf[i]='4';single=num-4*divid;break;
			case 5:
				buf[i]='5';single=num-5*divid;break;
			case 6:
				buf[i]='6';single=num-6*divid;break;
			case 7:
				buf[i]='7';single=num-7*divid;break;
			case 8:
				buf[i]='8';single=num-8*divid;break;
			case 9:
				buf[i]='9';single=num-9*divid;break;
			}
		}
	index = 4;
	}else{//Minuts and seconds always < 59

		for(int i=0;i<=1;i++)
		{
			if(i==0)
				single = num/10;

			switch (single)
			{
			case 0:
				buf[index]='0';single = num;break;
			case 1:
				buf[index]='1';single=num-1*10;break;
			case 2:
				buf[index]='2';single=num-2*10;break;
			case 3:
				buf[index]='3';single=num-3*10;break;
			case 4:
				buf[index]='4';single=num-4*10;break;
			case 5:
				buf[index]='5';single=num-5*10;break;
			case 6:
				buf[index]='6';single=num-6*10;break;
			case 7:
				buf[index]='7';single=num-7*10;break;
			case 8:
				buf[index]='8';single=num-8*10;break;
			case 9:
				buf[index]='9';single=num-9*10;break;
			}
		index++;
		}
	index++;
	}
}
}
//######################################## TRASH #############################################

