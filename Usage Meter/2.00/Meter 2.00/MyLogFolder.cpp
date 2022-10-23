// MyPath.cpp: implementation of the CMyLogFolder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "usage meter.h"
#include "DlgPath.h"
#include "MyLogFolder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
CMyLogFolder::CMyLogFolder(){}
CMyLogFolder::~CMyLogFolder(){}
//--------------------------------------------------------------------------------------------------------
bool CMyLogFolder::GetLogFolder(CString* plogfolder)
{
WIN32_FIND_DATA fd;
HANDLE			hfind;
char			path[256];
DWORD			len=256;

	RegGet(HKEY_LOCAL_MACHINE,"LogFolder",path,&len);

	//Check wether the folder is exist
	hfind = FindFirstFile(path, &fd);
	FindClose(hfind);
	if( (hfind==INVALID_HANDLE_VALUE) || (path[1]!=':') )
	{//Nop! folder is not there, so prompt for a new path
		if(SetLogFolder(plogfolder)==false)
			return false;
		len = plogfolder->GetLength();
		memcpy(path,plogfolder->GetBuffer(len),len);
		len++;
	}
	//Remove '*'
	path[len-2] = '\0';
	*plogfolder = path;
	return true;
}
//--------------------------------------------------------------------------------------------------------
bool CMyLogFolder::SetLogFolder(CString* plogfolder)
{//Ask user to enter path
CDlgPath dlg_path;
	dlg_path.m_plogpath = plogfolder;
	dlg_path.m_pprivilage = m_pprivilage;
	dlg_path.DoModal();
	if(dlg_path.m_errer==true)
		return false;
	else
		return true;
}
