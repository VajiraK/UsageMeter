// MyTime.cpp: implementation of the CMyTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyTime.h"

CMyTime::CMyTime()
{}
CMyTime::~CMyTime()
{}
//--------------------------------------------------------------------------------------------
void CMyTime::SetTime()
{
SYSTEMTIME	st; 

	GetLocalTime(&st);

	m_now[0] = (BYTE)st.wHour;
	m_now[1] = (BYTE)st.wMinute;
	m_now[2] = (BYTE)st.wSecond;
}


