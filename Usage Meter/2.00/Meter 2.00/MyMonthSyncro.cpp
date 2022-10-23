// MyMonthSyncro.cpp: implementation of the CMyMonthSyncro class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Usage Meter.h"
#include "MyMonthSyncro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
CMyMonthSyncro::CMyMonthSyncro()
{
	m_regmonth=RegGet(HKEY_LOCAL_MACHINE,"Month");
}
//////////////////////////////////////////////////////////////////////
bool CMyMonthSyncro::DetectMonChange()
{
 SYSTEMTIME	ST;
 DWORD	sys_mon;

	::GetLocalTime(&ST);
	sys_mon = ST.wMonth;
	if(sys_mon!=m_regmonth)
	{//month has changed
		//update registry
		m_regmonth = sys_mon;
		RegSet(HKEY_LOCAL_MACHINE,"Month",sys_mon);
		return true;
	}else{
		return false;
	}
}
//////////////////////////////////////////////////////////////////////
int CMyMonthSyncro::GetSystemMonth()
{
SYSTEMTIME ST;
	::GetLocalTime(&ST);
	return ST.wMonth;
}
//////////////////////////////////////////////////////////////////////
CString CMyMonthSyncro::NumToMothname(int monnum)
{
	switch(monnum)
	{
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	}
	return "invalid";
}


