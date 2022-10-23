// DlgBeepSetting.cpp : implementation file
//

#include "stdafx.h"
#include "usage meter.h"
#include "DlgBeepSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBeepSetting dialog
CDlgBeepSetting::CDlgBeepSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBeepSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBeepSetting)
	//}}AFX_DATA_INIT
}

void CDlgBeepSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBeepSetting)
	DDX_Control(pDX, EDIT_WIN_INTER, m_win_inter);
	DDX_Control(pDX, EDIT_WIN_FREE, m_win_free);
	DDX_Control(pDX, EDIT_WIN__DUR, m_win_dur);
	DDX_Control(pDX, EDIT_INT_INTER, m_int_inter);
	DDX_Control(pDX, EDIT_INT_FREE, m_int_free);
	DDX_Control(pDX, EDIT_INT__DUR, m_int_dur);
	DDX_Control(pDX, CHK_WIN_BEEP, m_win_chk);
	DDX_Control(pDX, CHK_INT_BEEP, m_int_chk);
	DDX_Control(pDX, IDC_STATIC_FRAM, m_fram);
	DDX_Control(pDX, IDC_TAB_BEEP, m_Tab_Beep);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgBeepSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgBeepSetting)
	ON_BN_CLICKED(IDC_TEST_BEEP, OnTestBeep)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_BEEP, OnSelchangingTabBeep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBeepSetting message handlers
BOOL CDlgBeepSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//Arrangeg coltrols
	m_Tab_Beep.InsertItem(0,"Internet");
	m_Tab_Beep.InsertItem(1,"Windows");
	m_Tab_Beep.SetWindowPos(&CWnd::wndBottom,5,4,235,94,SWP_SHOWWINDOW);
	m_fram.SetWindowPos(&CWnd::wndBottom,9,28,226,65,SWP_SHOWWINDOW);
RECT lpRect;
	this->GetWindowRect(&lpRect);
	this->SetWindowPos(&CWnd::wndBottom,lpRect.left+200,lpRect.top+308,249,149,SWP_SHOWWINDOW);

	//Internet tab selected first
	m_win_free.ShowWindow(0);
	m_win_dur.ShowWindow(0);
	m_win_inter.ShowWindow(0);
	m_win_chk.ShowWindow(0);
	m_int_free.SetWindowPos(&CWnd::wndBottom,73,37,35,20,SWP_SHOWWINDOW);
	m_int_inter.SetWindowPos(&CWnd::wndBottom,182,37,23,20,SWP_SHOWWINDOW);
	m_int_dur.SetWindowPos(&CWnd::wndBottom,73,65,35,20,SWP_SHOWWINDOW);
	m_int_chk.SetWindowPos(&CWnd::wndBottom,146,67,77,20,SWP_SHOWWINDOW);

	//Re_stor controls values
BEEP_STRUCT bs;
char	temp[5];
	//Internet
	m_beep_cls.RetriveSettings(&bs,false);
	m_beep_cls.CheckInputs(&bs,false,NULL);
	m_old_int_interval = bs.Interval;
	m_int_free.SetWindowText(_ltoa(bs.Frequency,temp,10));
	m_int_dur.SetWindowText(_ltoa(bs.Duration,temp,10));
	m_int_inter.SetWindowText(_ltoa(bs.Interval,temp,10));
	if(bs.Enable==1)
	{
		m_old_int_chkstate = 1;
		m_int_chk.SetCheck(1);
	}else{
		m_old_int_chkstate = 0;
		m_int_chk.SetCheck(0);
	}
	//Windows
	m_beep_cls.RetriveSettings(&bs,true);
	m_beep_cls.CheckInputs(&bs,false,NULL);
	m_old_win_interval = bs.Interval;
	//Re-stor controls values
	m_win_free.SetWindowText(_ltoa(bs.Frequency,temp,10));
	m_win_dur.SetWindowText(_ltoa(bs.Duration,temp,10));
	m_win_inter.SetWindowText(_ltoa(bs.Interval,temp,10));
	if(bs.Enable==1)
	{
		m_old_win_chkstate = 1;
		m_win_chk.SetCheck(1);
	}else{
		m_old_win_chkstate = 0;
		m_win_chk.SetCheck(0);
	}
	return TRUE; 
}
//--------------------------------------------------------------------------
void CDlgBeepSetting::OnTestBeep() 
{
BEEP_STRUCT bs;
char		temp[5];
	//Set fake value to Interval member
	bs.Interval = 10;

	if(m_Tab_Beep.GetItemState(1,1) == 0)
	{//Internet
		m_int_free.GetWindowText(temp,5);
		bs.Frequency = atoi(temp);
		m_int_dur.GetWindowText(temp,5);
		bs.Duration = atoi(temp);
	}
	else
	{//Windows
		m_win_free.GetWindowText(temp,5);
		bs.Frequency = atoi(temp);
		m_win_dur.GetWindowText(temp,5);
		bs.Duration = atoi(temp);
	};
	//Do beep
	if(m_beep_cls.CheckInputs(&bs,true,this->m_hWnd)==true)
		Beep(bs.Frequency,bs.Duration);
}
//--------------------------------------------------------------------------
void CDlgBeepSetting::OnOK() 
{
BEEP_STRUCT bs;
char		temp[5];
int			new_chk_state;
//Internet *********************************************************************************************
	m_int_free.GetWindowText(temp,5);
	bs.Frequency = atoi(temp);
	m_int_dur.GetWindowText(temp,5);
	bs.Duration = atoi(temp);
	m_int_inter.GetWindowText(temp,5);
	bs.Interval = atoi(temp);

	if(m_beep_cls.CheckInputs(&bs,true,this->m_hWnd)==true)
	{
		m_beep_cls.RegSet(HKEY_CURRENT_USER,"IntFrequency",(DWORD)bs.Frequency);
		m_beep_cls.RegSet(HKEY_CURRENT_USER,"IntDuration",(DWORD)bs.Duration);
		m_beep_cls.RegSet(HKEY_CURRENT_USER,"IntInterval",(DWORD)bs.Interval);
		if(m_int_chk.GetCheck()==1)
		{
			new_chk_state = 1;
			m_beep_cls.RegSet(HKEY_CURRENT_USER,"IntEnable",(DWORD)1);
		}
		else
		{
			new_chk_state = 0;
			m_beep_cls.RegSet(HKEY_CURRENT_USER,"IntEnable",(DWORD)0);
		}
	//If interval dosn't changed there is no neet to change
		//the counters beep count (m_reset_count's value check in Main Dialog)
	if((m_old_int_interval==bs.Interval)&&(m_old_int_chkstate==new_chk_state))
		m_reset_int_count = false;
	else
		m_reset_int_count = true;
	}
	else
		return;
//Windows *********************************************************************************************
	m_win_free.GetWindowText(temp,5);
	bs.Frequency = atoi(temp);
	m_win_dur.GetWindowText(temp,5);
	bs.Duration = atoi(temp);
	m_win_inter.GetWindowText(temp,5);
	bs.Interval = atoi(temp);

	if(m_beep_cls.CheckInputs(&bs,true,this->m_hWnd)==true)
	{	
		m_beep_cls.RegSet(HKEY_CURRENT_USER,"WinFrequency",(DWORD)bs.Frequency);
		m_beep_cls.RegSet(HKEY_CURRENT_USER,"WinDuration",(DWORD)bs.Duration);
		m_beep_cls.RegSet(HKEY_CURRENT_USER,"WinInterval",(DWORD)bs.Interval);
		if(m_win_chk.GetCheck()==1)
		{
			new_chk_state = 1;
			m_beep_cls.RegSet(HKEY_CURRENT_USER,"WinEnable",(DWORD)1);
		}
		else
		{
			new_chk_state = 0;
			m_beep_cls.RegSet(HKEY_CURRENT_USER,"WinEnable",(DWORD)0);
		}

		if((m_old_win_interval==bs.Interval)&&(m_old_win_chkstate==new_chk_state))
		m_reset_win_count = false;
		else
		m_reset_win_count = true;
	CDialog::OnOK();
	}
}
//--------------------------------------------------------------------------------
void CDlgBeepSetting::OnSelchangingTabBeep(NMHDR* pNMHDR, LRESULT* pResult) 
{
//Tab changed
		if(m_Tab_Beep.GetItemState(1,1) == 1)
		{//Internet
			m_win_free.ShowWindow(0);
			m_win_dur.ShowWindow(0);
			m_win_inter.ShowWindow(0);
			m_win_chk.ShowWindow(0);
			m_int_free.SetWindowPos(&CWnd::wndBottom,73,37,35,20,SWP_SHOWWINDOW);
			m_int_inter.SetWindowPos(&CWnd::wndBottom,182,37,23,20,SWP_SHOWWINDOW);
			m_int_dur.SetWindowPos(&CWnd::wndBottom,73,65,35,20,SWP_SHOWWINDOW);
			m_int_chk.SetWindowPos(&CWnd::wndBottom,146,67,77,20,SWP_SHOWWINDOW);
		}
		else
		{//Windows
			m_int_free.ShowWindow(0);
			m_int_dur.ShowWindow(0);
			m_int_inter.ShowWindow(0);
			m_int_chk.ShowWindow(0);
			m_win_free.SetWindowPos(&CWnd::wndBottom,73,37,35,20,SWP_SHOWWINDOW);
			m_win_inter.SetWindowPos(&CWnd::wndBottom,182,37,23,20,SWP_SHOWWINDOW);
			m_win_dur.SetWindowPos(&CWnd::wndBottom,73,65,35,20,SWP_SHOWWINDOW);
			m_win_chk.SetWindowPos(&CWnd::wndBottom,146,67,77,20,SWP_SHOWWINDOW);
		};
	*pResult = 0;
}
//-----------------------------------------------------------------------------------------------------
