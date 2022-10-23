// MyDate.cpp: implementation of the CMyDate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyDate.h"

CMyDate::CMyDate()
{}
CMyDate::~CMyDate()
{}
//-------------------------------------------------------------------------------------------
void CMyDate::QuarryDate()
{
	//DAY************************************************
	if( m_pre_day!=(BYTE)m_st.wDay )
	{//Date changed
		m_day_changed = true;
		SetMonthName();
	}else{
		m_day_changed = false;
	}

	//MONTH**********************************************
	if( m_pre_month!=(BYTE)m_st.wMonth )
	{//month has changed
		m_pre_month = (BYTE)m_st.wMonth;
		m_month_changed = true;
		return;
	}else{
		m_month_changed = false;
		return;
	}
}
//--------------------------------------------------------------------------------------------
void CMyDate::UpdateDate()
{
	//GetLocalTime(&m_st);
	m_pre_day=(BYTE)m_st.wDay;
}
//--------------------------------------------------------------------------------------------
void CMyDate::SetTime()
{
	GetLocalTime(&m_st);
	m_now[0] = (BYTE)m_st.wHour;
	m_now[1] = (BYTE)m_st.wMinute;
	m_now[2] = (BYTE)m_st.wSecond;
}
//--------------------------------------------------------------------------------------------
void CMyDate::SetDate()
{
	//Date
	m_pre_day = (BYTE)m_st.wDay;
	//Month
	m_pre_month = (BYTE)m_st.wMonth;
	//Set window title
	SetMonthName();
}
//-----------------------------------------------------------------------------------------
void CMyDate::SetMonthName()
{
char	year[5],day[3];
char	title[34];

	switch(m_pre_month)
	{
	case 1:
		memcpy(m_month_name,"Jan-",4);
		break;
	case 2:
		memcpy(m_month_name,"Feb-",4);
		break;
	case 3:
		memcpy(m_month_name,"Mar-",4);
		break;
	case 4:
		memcpy(m_month_name,"Apr-",4);
		break;
	case 5:
		memcpy(m_month_name,"May-",4);
		break;
	case 6:
		memcpy(m_month_name,"Jun-",4);
		break;
	case 7:
		memcpy(m_month_name,"Jul-",4);
		break;
	case 8:
		memcpy(m_month_name,"Aug-",4);
		break;
	case 9:
		memcpy(m_month_name,"Sep-",4);
		break;
	case 10:
		memcpy(m_month_name,"Oct-",4);
		break;
	case 11:
		memcpy(m_month_name,"Nov-",4);
		break;
	case 12:
		memcpy(m_month_name,"Dec-",4);
	}

	NumToString(year,m_st.wYear);
	memcpy(m_month_name+4,year,4);
	NumToString(day,m_st.wDay,(BYTE)1);
	memcpy(title,"Usage Meter 3.00 (  -",21);
	memcpy(title+18,day,2);
	memcpy(title+21,m_month_name,8);
	memcpy(title+29,")\0",2);
	
	SetWindowText(m_hmain_window,title);
}