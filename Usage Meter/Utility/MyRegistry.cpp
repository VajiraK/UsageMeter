// MyRegistry.cpp: implementation of the CMyRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyRegistry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////////////
CMyRegistry::CMyRegistry()
{
	#ifdef _DEBUG
	m_reg_key = "SOFTWARE\\Malwatta\\UsageMeter Debug";
	#else
	m_reg_key = "SOFTWARE\\Malwatta\\Usage Meter";
	#endif
	//Prepaire Security Attributes
	m_secu_atri.nLength=sizeof(m_secu_atri);
	m_secu_atri.bInheritHandle=1;
	m_secu_atri.lpSecurityDescriptor=NULL;
	
}
///////////////////////////////////////////////////////////////////////////////////////
void CMyRegistry::RegSet(HKEY Hive,char* ValueName,DWORD Value)
{//DWORD
	//Open or Create Key
	RegCreateKeyEx(Hive,m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &m_secu_atri, &m_key_handle,NULL);
	//Set Value
	RegSetValueEx(m_key_handle,ValueName,0,REG_DWORD,(LPBYTE)&Value, sizeof(Value));
	//Close
	RegCloseKey(m_key_handle);
}
///////////////////////////////////////////////////////////////////////////////////////
void CMyRegistry::RegSet(HKEY Hive,char* ValueName,char* Value,DWORD size)
{//STRING
	//Open or Create Key
	RegCreateKeyEx(Hive,m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &m_secu_atri, &m_key_handle,NULL);
	//Set Value
	RegSetValueEx(m_key_handle,ValueName,0,REG_SZ,(LPBYTE)Value, size);
	//Close
	RegCloseKey(m_key_handle);
}
///////////////////////////////////////////////////////////////////////////////////////
DWORD CMyRegistry::RegGet(HKEY Hive,char* ValueName)
{//DWORD
DWORD size = 4;
BYTE Value[4]; 
	//Open or Create Key
	RegCreateKeyEx(Hive, m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &m_secu_atri, &m_key_handle,NULL);
	//Get Value
	if(RegQueryValueEx(m_key_handle,ValueName ,NULL,NULL,Value,&size)!=0)
		return 0;
	//Close
	RegCloseKey(m_key_handle);
	return *(DWORD*)Value;
}
///////////////////////////////////////////////////////////////////////////////////////
void CMyRegistry::RegGet(HKEY Hive,char* ValueName,char* chrval,DWORD* size)
{//CHAR

	//Open or Create Key
	RegCreateKeyEx(Hive, m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &m_secu_atri, &m_key_handle,NULL);
	//Get Value
	if(RegQueryValueEx(m_key_handle,ValueName ,NULL,NULL,(BYTE*)chrval,size)!=0)
	{
		RegCloseKey(m_key_handle);
		return;
	}
	//Close
	RegCloseKey(m_key_handle);
}

