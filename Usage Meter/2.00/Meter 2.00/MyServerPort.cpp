// MyServerPort.cpp: implementation of the CMyServerPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Usage Meter.h"
#include "MyServerPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//----------------------------------------------------------------------------------
void CMyServerPort::SayServerActive(char* winstart,DWORD winroughdu)
{
	DWORD qustion = RegGet(HKEY_LOCAL_MACHINE,"ServerPort");

	if(qustion==MSG_IS_SERVER_RUNNING)
	{//ACTUALY ASKED A QUSTION
		//give ID
		m_client_count++;
		RegSet(HKEY_LOCAL_MACHINE,"ID",m_client_count);
		//give win start times
		RegSet(HKEY_LOCAL_MACHINE,"WinStartTime",winstart,8);
		//give win rough duration times
		RegSet(HKEY_LOCAL_MACHINE,"WinRoughDura",winroughdu);
		//supply answer
		RegSet(HKEY_LOCAL_MACHINE,"ServerPort",MSG_YES_RUNNUNG);
	}
}
//----------------------------------------------------------------------------------
void CMyServerPort::IntServerPortObj(DWORD* prilageref)
{
	m_pprivilage=prilageref;
	m_client_count=0;
	m_id=0;
}
//----------------------------------------------------------------------------------
bool CMyServerPort::GivePrivilage()
{
	//reset client port
	RegSet(HKEY_LOCAL_MACHINE,"ClientPort",MSG_INVALID);

	for(DWORD i=1;i<=m_client_count;i++)
	{
		//give client cout
		RegSet(HKEY_LOCAL_MACHINE,"ClientCount",m_client_count);
		//who can get the privilages
		RegSet(HKEY_LOCAL_MACHINE,"ID",i);
		//give privilage to client 
		RegSet(HKEY_LOCAL_MACHINE,"ServerPort",MSG_GET_PREVILIGE);
		::Sleep(600);

		if(MSG_GOT_PREVILIGE==RegGet(HKEY_LOCAL_MACHINE,"ClientPort"))
		{//some one got the privilage
			return true;
		}
	}

	return false;
}
