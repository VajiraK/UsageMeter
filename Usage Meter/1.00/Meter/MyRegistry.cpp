// MyRegistry.cpp: implementation of the CMyRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Usage Meter.h"
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

}
///////////////////////////////////////////////////////////////////////////////////////
void CMyRegistry::RegSet(HKEY Hive,char* ValueName,DWORD Value)
{//DWORD
SECURITY_ATTRIBUTES sa;
HKEY hKey;

	sa.nLength=sizeof(sa);
	sa.bInheritHandle=1;
	sa.lpSecurityDescriptor=NULL;
	//Open or Create Key
	RegCreateKeyEx(Hive,m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	//Set Value
	RegSetValueEx(hKey,ValueName,0,REG_DWORD,(LPBYTE)&Value, sizeof(Value));
	//Close
	RegCloseKey(hKey);
}
///////////////////////////////////////////////////////////////////////////////////////
void CMyRegistry::RegSet(HKEY Hive,char* ValueName,char* Value,DWORD size)
{//STRING
SECURITY_ATTRIBUTES sa;
HKEY hKey;

	sa.nLength=sizeof(sa);
	sa.bInheritHandle=1;
	sa.lpSecurityDescriptor=NULL;
	//Open or Create Key
	RegCreateKeyEx(Hive,m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	//Set Value
	RegSetValueEx(hKey,ValueName,0,REG_SZ,(LPBYTE)Value, size);
	//Close
	RegCloseKey(hKey);
}
///////////////////////////////////////////////////////////////////////////////////////
DWORD CMyRegistry::RegGet(HKEY Hive,char* ValueName)
{//DWORD
SECURITY_ATTRIBUTES sa;
HKEY hKey;
DWORD size = 100;
BYTE Value[100]; 
	
	sa.nLength=sizeof(sa);
	sa.bInheritHandle=1;
	sa.lpSecurityDescriptor=NULL;
	//Open or Create Key
	RegCreateKeyEx(Hive, m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	//Get Value
	if (RegQueryValueEx(hKey,ValueName ,NULL,NULL,Value,&size)!=0)
		return 0;

	//Close
	RegCloseKey(hKey);
	return *(DWORD*)Value;
}
///////////////////////////////////////////////////////////////////////////////////////
void CMyRegistry::RegGet(HKEY Hive,char* ValueName,CString* strval)
{//STRING
SECURITY_ATTRIBUTES sa;
HKEY hKey;
DWORD size=100;
BYTE Value[100]; 
	
	sa.nLength=sizeof(sa);
	sa.bInheritHandle=1;
	sa.lpSecurityDescriptor=NULL;
	//Open or Create Key
	RegCreateKeyEx(Hive, m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	//Get Value
	if (RegQueryValueEx(hKey,ValueName ,NULL,NULL,Value,&size)!=0)
	{
		*strval = "xxxxxx";
		return ;
	}

	//Close
	RegCloseKey(hKey);
	*strval = Value;
}

