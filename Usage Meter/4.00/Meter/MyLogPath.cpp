// MyLogPath.cpp: implementation of the CMyLogPath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MyLogPath.h"

CMyLogPath::CMyLogPath()
{}
CMyLogPath::~CMyLogPath()
{}
//----------------------------------------------------------------------------------------------
bool CMyLogPath::GetLogPath(char* path,DWORD size,DWORD* len)
{
bool ret;

	//Get path from registry
	ret = RegGet(HKEY_LOCAL_MACHINE,"LogFolder",path,size,len);
	if(ret)
		ret = IsFolderExist(path,len);

	if(ret==false)
	{
	//Nop! folder is not there, so prompt for a new path
		if(SetLogFolder()==false)
		{
			return false;
		}else
		{
			//Get path from registry again
			if (RegGet(HKEY_LOCAL_MACHINE, "LogFolder", path, size, len))
			{
				if((IsFolderExist(path,len)))
				{
					AddFileName(path,len);
					return true;
				}else{
					return false;
				}
			}else{
				return false;
			}
		}

	}else
	{
	//Add file name
	AddFileName(path,len);
	return true;
	}
}
//---------------------------------------------------------------------------------------------
bool CMyLogPath::SetLogFolder()
{//Ask user to enter path

	//Send cus msg to main wnd to 
	if (ID_SET_PATH == SendMessage(m_hmain_window,WM_COMMAND,MAKEWPARAM(ID_SHOW_PATH_DLG,0),NULL))
	{//OK press in PATH_DLG
		return true;
	}else{
		/*m_ex.kill = true;
		m_ex.err  = true;*/
		return false;
	}
}
//--------------------------------------------------------------------------------------
bool CMyLogPath::IsFolderExist(char *path, DWORD *len)
{
WIN32_FIND_DATA fd;
HANDLE			hfind;

	//Make path like "c:\log\*"
	*len -= 1;
	memcpy(path+*len,"*\0",2);

	//Check wether the folder is exist
	hfind = FindFirstFile(path, &fd);
	
	//Remove *
	path[*len] = '\0';

	if(hfind==INVALID_HANDLE_VALUE)
	{
		/*AddExeption("Cannot find the log folder!!");
		m_ex.code = GetLastError();
		m_ex.err = true;*/
		return false;

	}else{
		FindClose(hfind);
		m_ex.err = false;
		return true;
	}
}
//-------------------------------------------------------------------------------------------
void CMyLogPath::AddFileName(char *path, DWORD *len)
{

	SetMonthName();

	memcpy(path+(*len),m_month_name,8);
	*len += 8;
	memcpy(path+(*len),".umf\0",5);
	*len += 4;

	return;
}
