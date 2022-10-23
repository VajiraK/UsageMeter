// MyLogFile.cpp: implementation of the CMyLogFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MyLogFile.h"

CMyLogFile::~CMyLogFile(){}
//----------------------------------------------------------------------------------------------
CMyLogFile::CMyLogFile(){}
//---------------------------------------------------------------------------------------------
bool CMyLogFile::LoadLog()
{
	m_skip_timer = true;
	m_logthread_data.hlogfile = 0;

	//Get handle to the log file
	if(OpenLogFile()==false)
	{//Error
		m_skip_timer = false;
		CloseHandle(m_logthread_data.hlogfile);
		return false;
	}
	
	m_skip_timer = false;

	m_logthread_data.len = GetFileSize(m_logthread_data.hlogfile, NULL);
	//Empty file
	if(m_logthread_data.len<=27)
	{
		memcpy(m_int_total,"000:00:00",9);
		memcpy(m_win_total,"000:00:00",9);
		CloseHandle(m_logthread_data.hlogfile);
		return true;
	}
	
	m_logthread_data.len = m_logthread_data.len-27;
	m_logthread_data.data = new BYTE[m_logthread_data.len+1];

	SetFilePointer(m_logthread_data.hlogfile,27,NULL,FILE_BEGIN);
	//Get all data at once
	if(ReadFile(m_logthread_data.hlogfile,m_logthread_data.data,m_logthread_data.len,&m_logthread_data.len,NULL)==0)
	{
		m_ex.code = GetLastError();
		m_ex.err = true;
		m_ex.kill = true;
		CloseHandle(m_logthread_data.hlogfile);
		return false;
	}

	SendMessage(m_hmain_window,WM_COMMAND,MAKEWPARAM(ID_FILL_LIST,0),(LPARAM)&m_logthread_data);
	return true;
}
//----------------------------------------------------------------------------------------------
void CMyLogFile::Save_Win_Usage()
{
	m_um_log.type	= ID_WIN_LOG;
	m_um_log.day	= m_pre_day;

	memcpy(m_um_log.start, m_win_str_time, 3);
	memcpy(m_um_log.end, m_now, 3);
	memcpy(m_um_log.duration, m_pwin_counter->m_duration.num_dura, 3);

	SetLogonUsers();	
	SaveLog();
}
//----------------------------------------------------------------------------------------------
void CMyLogFile::Save_Int_Usage()
{
	m_um_log.type	= ID_INT_LOG;
	m_um_log.day	= m_pre_day;

	memcpy(m_um_log.start, m_int_str_time, 3);
	memcpy(m_um_log.end, m_now, 3);
	memcpy(m_um_log.duration, m_pint_counter->m_duration.num_dura, 3);
	
	/*m_um_log.type	= ID_INT_LOG;
	m_um_log.day	= 1;
	m_um_log.start[0] = m_um_log.start[1] = m_um_log.start[2] = 0;
	m_um_log.end[0] = m_um_log.end[1] = m_um_log.end[2] = 0;
	m_um_log.duration[0] = 4;
	m_um_log.duration[1] = 40;
	m_um_log.duration[2] = 0;*/

	SetActiveUsers();
	//for(int i=0;i<=900;i++)
	SaveLog();
}
//------------------------------------------------------------------------------------------------
void CMyLogFile::SaveLog()
{
BYTE	buffer[290];
DWORD	len;
	
	m_skip_timer = true;
	m_logthread_data.hlogfile = 0;

	//Get handle to the log file
	if(OpenLogFile()==false)
	{
		m_ex.kill = true;
		CloseHandle(m_logthread_data.hlogfile);
		return;
	}

	//Set file poiter to the EOF
	len = GetFileSize(m_logthread_data.hlogfile, NULL);
	SetFilePointer(m_logthread_data.hlogfile, len, NULL, FILE_BEGIN);

//*************Lets write log***********************************
	
	len = 16;
	memcpy(buffer,&m_um_log,len);//Log structure without (char*	user) 
	memcpy(buffer+len,m_um_log.users,m_um_log.users_len);//User name
	len += m_um_log.users_len;

	//Encrypt
	for(DWORD i=0;i<=len;i++)
		buffer[i] = buffer[i]^130;

	if(WriteFile(m_logthread_data.hlogfile,buffer,len,&len,NULL)!=0)
	{//Log succesfully written
		CloseHandle(m_logthread_data.hlogfile);
		m_skip_timer = false;
		return;

//*************Lets write log***********************************
	}
	else
	{//Error WriteFile
		CloseHandle(m_logthread_data.hlogfile);
		/*m_ex.err	= true;
		m_ex.code	= GetLastError();
		AddExeption("Cannot write to the log file!");*/
		return;
	}
}
//----------------------------------------------------------------------------------------------
void CMyLogFile::AssosiateFiles()
{
SECURITY_ATTRIBUTES sa;
HKEY				hKey;
DWORD				len;
char				apppath[MAX_PATH];

	sa.nLength=sizeof(sa);
	sa.bInheritHandle		= 1;
	sa.lpSecurityDescriptor = NULL;

	//CREATE RUN KEY ************************************
	/*len = GetModuleFileName(NULL,apppath,MAX_PATH);
	if(len==0)
	{//Cannot get application path
		m_ex.code = GetLastError();
		m_ex.err = true;
		AddExeption("Cannot get the application path!");
	}
	RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &sa, &hKey,NULL);
	RegSetValueEx(hKey,"UsageMeter",0,REG_SZ,(LPBYTE)apppath, len);
	RegCloseKey(hKey);*/
	//CREATE RUN KEY ************************************

	GetViewerPath(apppath,&len);

	RegCreateKeyEx(HKEY_CLASSES_ROOT,".umf",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &sa, &hKey,NULL);
	RegSetValueEx(hKey,NULL,0,REG_SZ,(LPBYTE)"usagemeterfile", 14);
	RegCloseKey(hKey);

	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &sa, &hKey,NULL);
	RegSetValueEx(hKey,NULL,0,REG_SZ,(LPBYTE)"Usage Meter Log File", 20);
	RegSetValueEx(hKey,"NeverShowExt",0,REG_SZ,(LPBYTE)"", 0);
	RegCloseKey(hKey);
	//DefaultIcon
	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile\\DefaultIcon",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &sa, &hKey,NULL);
	RegSetValueEx(hKey,NULL,0,REG_SZ,(LPBYTE)apppath, len);
	RegCloseKey(hKey);
	//Open command
	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile\\shell",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &sa, &hKey,NULL);
	RegCloseKey(hKey);
	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile\\shell\\Open",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &sa, &hKey,NULL);
	RegCloseKey(hKey);
	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile\\shell\\Open\\command",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &sa, &hKey,NULL);

	memcpy(apppath+len," %1",3);
	len = len + 3;
	m_ex.code = RegSetValueEx(hKey,NULL,0,REG_SZ,(LPBYTE)apppath, len);
				RegCloseKey(hKey);

	/*if( m_ex.code != ERROR_SUCCESS )
	{//Last func fail
		AddExeption("Cannot register Usage Meter log files!");
	}*/
}
//-----------------------------------------------------------------------------------------------
bool CMyLogFile::OpenLogFile()
{
WIN32_FIND_DATA fd;
HANDLE			hfind;
char			path[MAX_PATH];
DWORD			len;
static bool		try_count = false;
		
TRY_GAIN_PATH:

	//Get logging path
	if(GetLogPath(path,MAX_PATH,&len)==false)
		return false;
	
	//Check wether the file exist
	hfind = FindFirstFile(path, &fd);
	
	if(hfind==INVALID_HANDLE_VALUE)
	{//File is not there so try to create it
		m_logthread_data.hlogfile = CreateFile(path,GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_FLAG_RANDOM_ACCESS|FILE_ATTRIBUTE_NORMAL,NULL);
			
		if(m_logthread_data.hlogfile==INVALID_HANDLE_VALUE)
		{//cannot create
			/*m_ex.code = GetLastError();
			m_ex.err = true;
			AddExeption("Cannot create the log file!");*/
			return false;
		}else{
		//Write UM file header(Once and for all)
			if(WriteFile(m_logthread_data.hlogfile,"USAGE METER 3.00 LOG FILE\r\n",27,&len,NULL)==0)
			{//Error WriteFile
				CloseHandle(m_logthread_data.hlogfile);
				/*m_ex.err = true;
				m_ex.code = GetLastError();
				AddExeption("Cannot write to the log file header!");*/
				return  false;
			}else{
				return  true;
			}
		}

	}else{

		FindClose(hfind);
		//File is there lets try to open
		m_logthread_data.hlogfile = CreateFile(path,GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS|FILE_ATTRIBUTE_NORMAL,NULL);
				
		if(m_logthread_data.hlogfile==INVALID_HANDLE_VALUE)
		{//cannot open

			/*m_ex.err = true;
			m_ex.code = GetLastError();
			AddExeption("Cannot open the log file!");*/
			//Clear path reg key and try again
			RegSet(HKEY_LOCAL_MACHINE,"LogFolder","",0);

			if(try_count==false)
			{//Try again only once
				try_count=true;
				goto TRY_GAIN_PATH;
			}else
			{
				 return false;
			}
		}else{
			return true;
		}
	}
	return false;//Just to avoid warning
}
//-------------------------------------------------------------------------------------------------
void CMyLogFile::GetViewerPath(char *path,DWORD* len)
{
DWORD i;
	*len = GetModuleFileName(NULL,path,MAX_PATH);

	for(i=*len;i>=0;i--)
	{
		if(path[i]=='\\')
			break;
	}

	*len = i;
	memcpy(&path[i],"\\Viewer.exe\0",12);
	*len = *len + 12;
}
