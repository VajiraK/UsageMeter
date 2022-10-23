// MyServerPort.cpp: implementation of the CMyServerPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyServerPort.h"

CMyServerPort::CMyServerPort(){}
CMyServerPort::~CMyServerPort(){}

//----------------------------------------------------------------------------------
void CMyServerPort::SayServerActive()
{
DWORD qustion; 

	RegGet(HKEY_LOCAL_MACHINE,"ComPort",&qustion);

	if(qustion==MSG_IS_SERVER_RUNNING)
	{//ACTUALY ASKED A QUSTION
		//give ID
		m_client_count++;
		RegSet(HKEY_LOCAL_MACHINE,"ID",m_client_count);
		//give win start time and win duration
	BYTE temp[6];
		memcpy(temp,m_win_str_time,3);
		memcpy(&temp[3],m_pwin_counter->m_duration.num_dura,3);
		RegSetBinary(HKEY_LOCAL_MACHINE,"WinST_DR",temp,6);
		//supply answer
		RegSet(HKEY_LOCAL_MACHINE,"ComPort",MSG_YES_RUNNUNG);
	}
}
//----------------------------------------------------------------------------------
bool CMyServerPort::GivePrivilage()
{
DWORD answer;

	//reset client port
	RegSet(HKEY_LOCAL_MACHINE,"ClientPort",MSG_INVALID);

	for(DWORD i=1;i<=m_client_count;i++)
	{
		//give client cout
		RegSet(HKEY_LOCAL_MACHINE,"ClientCount",m_client_count);
		//who can get the privilages
		RegSet(HKEY_LOCAL_MACHINE,"ID",i);
		//give privilage to client 
		RegSet(HKEY_LOCAL_MACHINE,"ComPort",MSG_GET_PREVILIGE);
		::Sleep(600);

		RegGet(HKEY_LOCAL_MACHINE,"ClientPort",&answer);

		if(MSG_GOT_PREVILIGE==answer)
		{//some one got the privilage
			return true;
		}
	}

	return false;
}

