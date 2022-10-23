// MyClientPort.cpp: implementation of the CMyClientPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Usage Meter.h"
#include "MyClientPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//----------------------------------------------------------------------------------
void CMyClientPort::IsServerRunning(CString* winstart)
{
	//ask for run mode
	RegSet(HKEY_LOCAL_MACHINE,"ServerPort",IS_SERVER_RUNNING);
	::Sleep(1100);

	//check whether a answer given
DWORD ans = RegGet(HKEY_LOCAL_MACHINE,"ServerPort");
	if(ans==YES_RUNNUNG)
	{//server given a answer (I am a client)
		*m_pprivilage = CLIENT;
		//get my ID
		m_id=RegGet(HKEY_LOCAL_MACHINE,"ID");
		//get start times
		RegGet(HKEY_LOCAL_MACHINE,"WinStartTime",winstart);
	}else{//no answer (I am a server)
		*m_pprivilage = SERVER;
	}

	//invalidate ServerPort
	RegSet(HKEY_LOCAL_MACHINE,"ServerPort",INVALID);
}
//----------------------------------------------------------------------------------
void CMyClientPort::GrantPrivilages(HWND main_dlg)
{
	//ask for privilages
	DWORD answer = RegGet(HKEY_LOCAL_MACHINE,"ServerPort");

	if(answer==GET_PREVILIGE)
	{//server given privilages
		DWORD id = RegGet(HKEY_LOCAL_MACHINE,"ID");
		if(m_id==id)
		{//given to me
			//Invalidate ServerPort
			RegSet(HKEY_LOCAL_MACHINE,"ServerPort",INVALID);
			//kill server comunication
			KillTimer(main_dlg,ID_SERVER_LINK_TIMER);
			//get client count
			m_client_count=RegGet(HKEY_LOCAL_MACHINE,"ClientCount");
			//say to server that I got privillages
			RegSet(HKEY_LOCAL_MACHINE,"ClientPort",GOT_PREVILIGE);
			//assign privilage
			*m_pprivilage = SERVER;
		}
	}
}


