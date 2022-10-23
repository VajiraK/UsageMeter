// MyEventLog.cpp: implementation of the CMyEventLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyEventLog.h"

CMyEventLog::CMyEventLog(){}
//----------------------------------------------------------------------------------------------
CMyEventLog::~CMyEventLog()
{
	CloseHandle(hlogfile);
}
//---------------------------------------------------------------------------------------
void CMyEventLog::WriteLog(char *text)
{
DWORD	len,flen,c=50;
char	*buff,temp[5],user[50];
	//File handle invalied
	if(hlogfile==INVALID_HANDLE_VALUE)
		return;

	for(len=0;len<=200;len++)
	{
		if(text[len]=='\0')
			break;
	}

	GetUserName(user,&c);
	buff = new char[(len + c + 35)];
	
	flen = GetFileSize(hlogfile, NULL);
	if(flen>1048576)
	{//File is too big(1MB) lets open a new file
		CloseHandle(hlogfile);
		DeleteFile(m_path);
		hlogfile = CreateFile(m_path,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_NEW,FILE_FLAG_RANDOM_ACCESS|FILE_ATTRIBUTE_NORMAL,NULL);
	}else{//Set file poiter to the EOF
		SetFilePointer(hlogfile, flen, NULL, FILE_BEGIN);
	}
	
	//Date and time
	MakeStrTime(&m_time[11],m_now);
	NumToString(temp,m_st.wYear);
	memcpy(m_time,temp,4);
	NumToString(temp,m_st.wMonth,(BYTE)1);
	memcpy(&m_time[5],temp,2);
	NumToString(temp,m_st.wDay,(BYTE)1);
	memcpy(&m_time[8],temp,2);
	memcpy(buff,m_time,22);
	//ID
	buff[22] = '<';
	NumToString(&buff[21],m_id,(BYTE)1);
	memcpy(&buff[23],"> ",2);
	//Log
	memcpy(&buff[25],text,len);
	//User
	memcpy(&buff[25+len]," <",2);
	memcpy(&buff[27+len],user,c);
	memcpy(&buff[26+len+c],">\r\n",3);
	//Write to file
	len = len + c + 29;
	WriteFile(hlogfile,buff,len,&len,NULL);
	delete[] buff;
}
//---------------------------------------------------------------------------------------
void CMyEventLog::IntEventLog()
{
WIN32_FIND_DATA fd;
HANDLE			hfind;
DWORD			len,i;

	len = GetModuleFileName(NULL,m_path,MAX_PATH);
	for(i=len;i>=0;i--)
	{
		if(m_path[i]=='\\')
			break;
	}
	memcpy(&m_path[i],"\\meter.log\0",11);

	//Check wether the file exist
	hfind = FindFirstFile(m_path, &fd);
	FindClose(hfind);

	hlogfile = NULL;

	if(hfind==INVALID_HANDLE_VALUE)
		hlogfile = CreateFile(m_path,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,CREATE_NEW,FILE_FLAG_RANDOM_ACCESS|FILE_ATTRIBUTE_NORMAL,NULL);
	else
		hlogfile = CreateFile(m_path,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS|FILE_ATTRIBUTE_NORMAL,NULL);

	//prepaire time buffer
	m_time[4] = m_time[7] = '-';
	m_time[10] = ' ';
	m_time[13] = m_time[16] = ':';
	memcpy(&m_time[19]," <",2);
}
//---------------------------------------------------------------------------------------
void CMyEventLog::AddLine()
{
DWORD	len=2;

	//File handle invalied
	if(hlogfile==NULL)
		return;

	SetFilePointer(hlogfile, GetFileSize(hlogfile, NULL), NULL, FILE_BEGIN);
	
	WriteFile(hlogfile,"\r\n",len,&len,NULL);
}
