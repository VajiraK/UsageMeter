// MyExceptions.cpp: implementation of the CMyExceptions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MyExceptions.h"


CMyExceptions::~CMyExceptions(){}
//------------------------------------------------------------------------------------------------
CMyExceptions::CMyExceptions()
{
	m_ex.code		= 0;
	m_ex.list_len	= 0;
}
//------------------------------------------------------------------------------------------------
/*void CMyExceptions::AddExeption(char* exeption)
{
LPVOID	lpMsgBuf;
DWORD	sysmsg_len;
int		i;

	for(i=0;i<=200;i++)
	{
		if(exeption[i]=='\0')
			break;
	}
	//Copy custom msg
	memcpy(&m_ex.list_ex[m_ex.list_len],exeption,i);
	m_ex.list_len += i;
	memcpy(&m_ex.list_ex[m_ex.list_len],"\r\n",2);
	m_ex.list_len += 2;

	if(m_ex.code!=0)
	{//Has system err msg
		sysmsg_len = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,
									m_ex.code,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0,NULL);
		//Clear code
		m_ex.code = 0;
		//Copy sys msg
		sysmsg_len--;
		memcpy(&m_ex.list_ex[m_ex.list_len],"System says - ",14);
		m_ex.list_len += 14;
		memcpy(&m_ex.list_ex[m_ex.list_len],lpMsgBuf,sysmsg_len);
		m_ex.list_len += sysmsg_len;
		memcpy(&m_ex.list_ex[m_ex.list_len],"\r\n\r\n\0",5);
		m_ex.list_len += 4;
		// Free the buffer.
		LocalFree(lpMsgBuf);
	}

}
//------------------------------------------------------------------------------------------------
void CMyExceptions::ClearExeptions()
{
	m_ex.list_len = 0;
	m_ex.err	  = false;
}
//------------------------------------------------------------------------------------------------
void CMyExceptions::ShowExeptions(bool isfloat)
{
	if(isfloat)
		SendMessage(m_hmain_window,WM_COMMAND,MAKEWPARAM(ID_SHOW_FLOAT_EXEP,0),NULL);
	else
		SendMessage(m_hmain_window,WM_COMMAND,MAKEWPARAM(ID_SHOW_EXEPTION,0),NULL);

	ClearExeptions();
}*/
