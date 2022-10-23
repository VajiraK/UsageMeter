// MyMonthSyncro.cpp: implementation of the CMyMonthSyncro class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyMonthSyncro.h"

CMyMonthSyncro::CMyMonthSyncro()
{}
CMyMonthSyncro::~CMyMonthSyncro()
{}
//------------------------------------------------------------------------------------------
DWORD CMyMonthSyncro::DetectMonChange(bool* pchanged)
{
SYSTEMTIME	ts;
DWORD		sysmon, regmonth;
	
	m_retval = RegGet(HKEY_LOCAL_MACHINE,"Month",&regmonth);
	GetLocalTime(&ts);
	sysmon = ts.wMonth;

	if( sysmon!=regmonth )
	{//month has changed

		regmonth = sysmon;
		*pchanged = true;
		return RegSet(HKEY_LOCAL_MACHINE,"Month",sysmon);
	}
	else
	{
		*pchanged = false;
		return m_retval;
	}
}
