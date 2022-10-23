// MyGlobal.cpp: implementation of the CMyGlobal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyGlobal.h"

CMyGlobal::~CMyGlobal()
{}
//------------------------------------------------------------------------------------------
CMyGlobal::CMyGlobal()
{
	m_um_log.users = NULL;
	m_skip_timer	= false;
}
