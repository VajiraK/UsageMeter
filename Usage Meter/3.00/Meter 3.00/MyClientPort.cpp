// MyClienPort.cpp: implementation of the CMyClienPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyClientPort.h"

CMyClientPort::CMyClientPort(){}
CMyClientPort::~CMyClientPort(){}

//----------------------------------------------------------------------------------
void CMyClientPort::IsServerRunning()
{
DWORD ans;

	//ask for run mode
	RegSet(HKEY_LOCAL_MACHINE,"ServerPort",MSG_IS_SERVER_RUNNING);
	Sleep(1100);

	//check whether a answer given
	RegGet(HKEY_LOCAL_MACHINE,"ServerPort",&ans);
	if(ans==MSG_YES_RUNNUNG)
	{//server given a answer (I am a client)
		m_privilage = CLIENT;
		//get my ID
		RegGet(HKEY_LOCAL_MACHINE,"ID",&m_id);
		//get win start time and win duration
	BYTE temp[6];
		RegGetBinary(HKEY_LOCAL_MACHINE,"WinST_DR",temp,6);
		memcpy(m_win_str_time,temp,3);
		memcpy(m_pwin_counter->m_duration.num_dura,&temp[3],3);
	}else{//no answer (I am a server)
		m_privilage = SERVER;
	}

	//invalidate ServerPort
	RegSet(HKEY_LOCAL_MACHINE,"ServerPort",MSG_INVALID);
}
//----------------------------------------------------------------------------------
void CMyClientPort::GrantPrivilages()
{
DWORD answer,id;
	//ask for privilages
	 RegGet(HKEY_LOCAL_MACHINE,"ServerPort",&answer);

	if(answer==MSG_GET_PREVILIGE)
	{//server given privilages
		RegGet(HKEY_LOCAL_MACHINE,"ID",&id);
		if(m_id==id)
		{//given to me
			//Invalidate ServerPort
			RegSet(HKEY_LOCAL_MACHINE,"ServerPort",MSG_INVALID);
			//kill server comunication
			KillTimer(m_hmain_window,TIMER_SERVER_LINK);
			//get client count
			RegGet(HKEY_LOCAL_MACHINE,"ClientCount",&m_client_count);
			//say to server that I got privillages
			RegSet(HKEY_LOCAL_MACHINE,"ClientPort",MSG_GOT_PREVILIGE);
			//assign privilage
			m_privilage = SERVER;
		}
	}
}
