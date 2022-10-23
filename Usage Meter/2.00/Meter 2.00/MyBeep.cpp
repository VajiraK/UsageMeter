// MyBeep.cpp: implementation of the CMyBeep class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "usage meter.h"
#include "MyBeep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
///////////////////////////////////////////////////////////////////////////
CMyBeep::CMyBeep(){}
//-----------------------------------------------------------------------------
CMyBeep::~CMyBeep(){}
//-----------------------------------------------------------------------------
void CMyBeep::Beep()
{//Call by Counter Incrimet event (Client and Server both try to 
	//beep but XP only execute active users ask
	if(m_beep_info.Enable==true)
	{
		m_beep_info.Count++;
		if(m_beep_info.Count==m_beep_info.Interval)
		{
			::Beep(m_beep_info.Frequency,m_beep_info.Duration);
			ResetBeepCount();
		}
	}
}
//-----------------------------------------------------------------------------
void CMyBeep::SetBeep(BEEP_STRUCT* bs,bool reset_count)
{
	m_beep_info.Enable		= bs->Enable;
	m_beep_info.Duration	= bs->Duration;
	m_beep_info.Frequency	= bs->Frequency;
	m_beep_info.Interval	= (bs->Interval*60);
	if(reset_count==true)
		ResetBeepCount();
}
//-----------------------------------------------------------------------------
void CMyBeep::RetriveSettings(BEEP_STRUCT* bs, bool flag)
{
	if(flag==false)
	{//Internet
		bs->Frequency	= RegGet(HKEY_CURRENT_USER,"IntFrequency");
		bs->Duration	= RegGet(HKEY_CURRENT_USER,"IntDuration");
		bs->Interval	= RegGet(HKEY_CURRENT_USER,"IntInterval");
		if(RegGet(HKEY_CURRENT_USER,"IntEnable")==1)
			bs->Enable	= 1;	
		else
			bs->Enable	= 0;	
	}else{
	//Windows
		bs->Frequency	= RegGet(HKEY_CURRENT_USER,"WinFrequency");
		bs->Duration	= RegGet(HKEY_CURRENT_USER,"WinDuration");
		bs->Interval	= RegGet(HKEY_CURRENT_USER,"WinInterval");
		if(RegGet(HKEY_CURRENT_USER,"WinEnable")==1)
			bs->Enable	= 1;	
		else
			bs->Enable	= 0;
	}
}
//-----------------------------------------------------------------------------
bool CMyBeep::CheckInputs(BEEP_STRUCT* bs, bool show_err,HWND parent)
{
CString	msg;
bool	err = false;

	if((bs->Frequency<1000)||(bs->Frequency>4000))
	{
		err = true;
		bs->Frequency = 2500;
		msg = "Frequency must be in between 1000Hz - 4000Hz ";	
	}
	if((bs->Duration<10)||(bs->Duration>2000))
	{
		err = true;
		bs->Duration = 100;
		msg = "Duration must be in between 10ms - 2000ms ";
	}
	if((bs->Interval<1)||(bs->Interval>60))
	{	
		err = true;
		bs->Interval = 10;
		msg = "Interval must be in between 1min - 60min ";
	}
	
	if(err==true)
	{
		if(show_err==true)
		{
		::MessageBox(NULL,msg,"Usage Meter",MB_OK|MB_ICONEXCLAMATION);
		}
		return false;
	}else{
		return true;
	}
}
//-----------------------------------------------------------------------------
void CMyBeep::ResetBeepCount()
{
	m_beep_info.Count = 0;
}
