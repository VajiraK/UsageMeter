// MyBeepDlg.cpp: implementation of the CMyBeepDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyBeepDlg.h"
#include "resource.h"
#include <commctrl.h>

CMyBeepDlg::~CMyBeepDlg(){}
CMyBeepDlg::CMyBeepDlg(){}
//----------------------------------------------------------------------------------------------
void CMyBeepDlg::Initialize(MY_BEEP_STRUCT *pwinbeep, MY_BEEP_STRUCT *pintbeep,HWND me)
{
	m_pwin_beep	= pwinbeep;
	m_pint_beep	= pintbeep;
	m_me		= me;
}
//----------------------------------------------------------------------------------------------
void CMyBeepDlg::StartUp()
{
	SetUpWindow();
	RetrieveBeep();
}
//----------------------------------------------------------------------------------------------
void CMyBeepDlg::SetUpWindow()
{
TCITEM	ti;
HWND	temp;

	//Tab control 
	temp = GetDlgItem(m_me,IDC_TAB_BEEP);
	m_font_tab = CreateFont("Tahoma",6,13);
	SendMessage(temp,WM_SETFONT,(WPARAM)m_font_tab,MAKELPARAM(FALSE, 0));
	//Insert Tabs
	ti.mask = TCIF_TEXT ;ti.pszText = "Internet";ti.cchTextMax = 8;
	SendMessage(temp,TCM_INSERTITEM,(WPARAM)1,(LPARAM)&ti);
	ti.pszText = "Windows";ti.cchTextMax = 7;
	SendMessage(temp,TCM_INSERTITEM,(WPARAM)1,(LPARAM)&ti);
	MoveWindow(temp,5,5,250,95,false);
	//IDC_STATIC_FRAM
	temp = GetDlgItem(m_me,IDC_STATIC_FRAM);
	SetParent(temp,m_me);
	MoveWindow(temp,10,30,239,64,false);
	
	ShowWindow(GetDlgItem(m_me,EDIT_WIN_FREE),0);
	ShowWindow(GetDlgItem(m_me,EDIT_WIN_INTER),0);
	ShowWindow(GetDlgItem(m_me,EDIT_WIN__DUR),0);
	ShowWindow(GetDlgItem(m_me,CHK_WIN_BEEP),0);
	m_sel_tab = 0;

}
//----------------------------------------------------------------------------------------------
HFONT CMyBeepDlg::CreateFont(char* face,WORD len,WORD size)
{
LOGFONT lf;
HFONT	hfont;

	ZeroMemory(&lf,sizeof(LOGFONT));
	lf.lfHeight = size;
	memcpy(lf.lfFaceName,face,len);
	hfont = CreateFontIndirect(&lf);
	return hfont;
}
//--------------------------------------------------------------------------------------
void CMyBeepDlg::TabChanged(LPARAM lParam)
{
NMHDR* nr = (NMHDR*)lParam;

	if(nr->code==TCN_SELCHANGE)
	{
		if(SendMessage(GetDlgItem(m_me,IDC_TAB_BEEP),TCM_GETCURSEL,(WPARAM)0,(LPARAM)0)==0)
		{//Internet Tab
			ShowWindow(GetDlgItem(m_me,EDIT_WIN_FREE),0);
			ShowWindow(GetDlgItem(m_me,EDIT_WIN_INTER),0);
			ShowWindow(GetDlgItem(m_me,EDIT_WIN__DUR),0);
			ShowWindow(GetDlgItem(m_me,CHK_WIN_BEEP),0);
			ShowWindow(GetDlgItem(m_me,EDIT_INT_FREE),1);
			ShowWindow(GetDlgItem(m_me,EDIT_INT_INTER),1);
			ShowWindow(GetDlgItem(m_me,EDIT_INT_DUR),1);
			ShowWindow(GetDlgItem(m_me,CHK_INT_BEEP),1);
			m_sel_tab = 0;
		}else{
			ShowWindow(GetDlgItem(m_me,EDIT_WIN_FREE),1);
			ShowWindow(GetDlgItem(m_me,EDIT_WIN_INTER),1);
			ShowWindow(GetDlgItem(m_me,EDIT_WIN__DUR),1);
			ShowWindow(GetDlgItem(m_me,CHK_WIN_BEEP),1);
			ShowWindow(GetDlgItem(m_me,EDIT_INT_FREE),0);
			ShowWindow(GetDlgItem(m_me,EDIT_INT_INTER),0);
			ShowWindow(GetDlgItem(m_me,EDIT_INT_DUR),0);
			ShowWindow(GetDlgItem(m_me,CHK_INT_BEEP),0);
			m_sel_tab = 1;
		}
	}
}
//--------------------------------------------------------------------------------------------
bool CMyBeepDlg::SaveBeep()
{
char	temp[18];

	//Windows ********************************************
	GetWindowText(GetDlgItem(m_me,EDIT_WIN_FREE),temp,5);
	m_beep_arr[0].frequency = (WORD)atoi(temp);
	GetWindowText(GetDlgItem(m_me,EDIT_WIN__DUR),temp,5);
	m_beep_arr[0].duration = (WORD)atoi(temp);
	GetWindowText(GetDlgItem(m_me,EDIT_WIN_INTER),temp,5);
	m_beep_arr[0].interval = (WORD)atoi(temp);

	if(SendMessage(GetDlgItem(m_me,CHK_WIN_BEEP),BM_GETCHECK,0,0)==1)
		m_beep_arr[0].enable	= 1;
	else
		m_beep_arr[0].enable	= 0;
	//Windows  ********************************************

	//Internet ********************************************
	GetWindowText(GetDlgItem(m_me,EDIT_INT_FREE),temp,5);
	m_beep_arr[1].frequency = (WORD)atoi(temp);
	GetWindowText(GetDlgItem(m_me,EDIT_INT_DUR),temp,5);
	m_beep_arr[1].duration = (WORD)atoi(temp);
	GetWindowText(GetDlgItem(m_me,EDIT_INT_INTER),temp,5);
	m_beep_arr[1].interval = (WORD)atoi(temp);

	if(SendMessage(GetDlgItem(m_me,CHK_INT_BEEP),BM_GETCHECK,0,0)==1)
		m_beep_arr[1].enable	= 1;
	else
		m_beep_arr[1].enable	= 0;
	//Internet ********************************************

	if(CheckInputs())
	{//Inputs okey! yahooooooo........ hi...
		RegSetBinary(HKEY_CURRENT_USER,"BeepInfo",(BYTE*)m_beep_arr,22);
		SetCountersBeep();
	}
	else
		return false;

	return true;
}
//--------------------------------------------------------------------------------------------
bool CMyBeepDlg::CheckInputs(bool silent)
{
char	msg[60];
bool	err = false;

	for(int i=0;i<=1;i++)
	{
		if((m_beep_arr[i].frequency<40))
		{//Frequency
			err = true;
			if(i==0)
				strcpy_s(msg,60,"In Windows tab, Miminum value for frequency is 40Hz ");
			else
				strcpy_s(msg,60,"In Internet tab, Miminum value for frequency is 40Hz ");
		}
		if((m_beep_arr[i].duration<10)||(m_beep_arr[i].duration>2000))
		{//Duration
			err = true;
			if(i==0)
				strcpy_s(msg,60,"In Windows tab, Duration must be in between 10ms - 2000ms ");
			else
				strcpy_s(msg,60,"In Internet tab, Duration must be in between 10ms - 2000ms ");
		}
		if((m_beep_arr[i].interval<1))
		{//Interval
			err = true;
			if(i==0)
				strcpy_s(msg,60,"In Windows tab, Miminum value for interval is 1min ");	
			else
				strcpy_s(msg,60,"In Internet tab, Miminum value for interval is 1min ");	
		}

		if(err==true)
			break;
	}

	if(err==true)
	{
		if(silent==false)
			MessageBox(NULL,msg,"Usage Meter",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}
//------------------------------------------------------------------------------------------
void CMyBeepDlg::RetrieveBeep()
{
char	temp[10];

	RegGetBinary(HKEY_CURRENT_USER,"BeepInfo",(BYTE*)m_beep_arr,22);

	if(m_me!=NULL)
	{
		_ltoa_s(m_beep_arr[0].frequency,temp,10,10);
		SetWindowText(GetDlgItem(m_me,EDIT_WIN_FREE),temp);
		_ltoa_s(m_beep_arr[0].duration,temp,10,10);
		SetWindowText(GetDlgItem(m_me,EDIT_WIN__DUR),temp);
		_ltoa_s(m_beep_arr[0].interval,temp,10,10);
		SetWindowText(GetDlgItem(m_me,EDIT_WIN_INTER),temp);
		if(m_beep_arr[0].enable==1)
			SendMessage(GetDlgItem(m_me,CHK_WIN_BEEP),BM_SETCHECK,(WPARAM)BST_CHECKED,0);

		_ltoa_s(m_beep_arr[1].frequency,temp,10,10);
		SetWindowText(GetDlgItem(m_me,EDIT_INT_FREE),temp);
		_ltoa_s(m_beep_arr[1].duration,temp,10,10);
		SetWindowText(GetDlgItem(m_me,EDIT_INT_DUR),temp);
		_ltoa_s(m_beep_arr[1].interval,temp,10,10);
		SetWindowText(GetDlgItem(m_me,EDIT_INT_INTER),temp);
		if(m_beep_arr[1].enable==1)
			SendMessage(GetDlgItem(m_me,CHK_INT_BEEP),BM_SETCHECK,(WPARAM)BST_CHECKED,0);
	}

	if(CheckInputs(true)==false)
	{//Error in registry settings let's reset it
		m_beep_arr[0].frequency = 1000;
		m_beep_arr[0].duration	= 100;
		m_beep_arr[0].interval	= 60;
		m_beep_arr[0].enable	= 0;
		m_beep_arr[1].frequency = 2000;
		m_beep_arr[1].duration	= 100;
		m_beep_arr[1].interval	= 10;
		m_beep_arr[1].enable	= 0;
		RegSetBinary(HKEY_CURRENT_USER,"BeepInfo",(BYTE*)m_beep_arr,22);
		RetrieveBeep();
	}

}
//----------------------------------------------------------------------------------------------
void CMyBeepDlg::TestBeep()
{
WORD	f,d;
char	temp[5];
char	msg[50];
bool	err = false;

	if(m_sel_tab==0)
	{//Internet tab selected
		GetWindowText(GetDlgItem(m_me,EDIT_INT_FREE),temp,5);
		f = (WORD)atoi(temp);
		GetWindowText(GetDlgItem(m_me,EDIT_INT_DUR),temp,5);
		d = (WORD)atoi(temp);
	}else{
		GetWindowText(GetDlgItem(m_me,EDIT_WIN_FREE),temp,5);
		f = (WORD)atoi(temp);
		GetWindowText(GetDlgItem(m_me,EDIT_WIN__DUR),temp,5);
		d = (WORD)atoi(temp);
	}

	if((f<40))
	{//Frequency
		err = true;
		strcpy_s(msg,50,"Miminum value for frequency is 40Hz ");	
	}
	if((d<10)||(d>2000))
	{//Duration
		err = true;
		strcpy_s(msg,50,"Duration must be in between 10ms - 2000ms ");
	}

	if(err==true)
	{
		MessageBox(NULL,msg,"Usage Meter",MB_OK|MB_ICONEXCLAMATION);
	}else{
		Beep(f,d);
	}
}
//----------------------------------------------------------------------------------------------
void CMyBeepDlg::SetCountersBeep()
{
	//Windows
	m_pwin_beep->frequency	= m_beep_arr[0].frequency;
	m_pwin_beep->duration	= m_beep_arr[0].duration;
	m_pwin_beep->enable		= m_beep_arr[0].enable;

	if(m_pwin_beep->interval!=m_beep_arr[0].interval)
	{//Reset count if only interval changed
		m_pwin_beep->interval = m_beep_arr[0].interval * 60;//Convert to seconds
		m_pwin_beep->count	  = 0;
	}

	//Internet
	m_pint_beep->frequency	= m_beep_arr[1].frequency;
	m_pint_beep->duration	= m_beep_arr[1].duration;
	m_pint_beep->enable		= m_beep_arr[1].enable;

	if(m_pint_beep->interval!=m_beep_arr[1].interval)
	{//Reset count if only interval changed
		m_pint_beep->interval = m_beep_arr[1].interval * 60;//Convert to seconds
		m_pint_beep->count	  = 0;
	}
}
