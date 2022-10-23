// MyRegistry.cpp: implementation of the CMyRegistry class.


#include "stdafx.h"
#include "MyRegistry.h"

CMyRegistry::~CMyRegistry()
{}
//----------------------------------------------------------------------------
CMyRegistry::CMyRegistry()
{
#ifdef _DEBUG
	m_reg_key = "SOFTWARE\\Malwatta\\UsageMeter Debug";
#else
	m_reg_key = "SOFTWARE\\Malwatta\\Usage Meter3";
#endif

	//Prepaire Security Attributes
	m_secu_atri.nLength					= sizeof(m_secu_atri);
	m_secu_atri.bInheritHandle			= 1;
	m_secu_atri.lpSecurityDescriptor	= NULL;
}
//--------------------------------------------------------------------------------------------
bool CMyRegistry::RegGet(HKEY Hive,char* ValueName,DWORD* pvalue)
{//DWORD
DWORD	ret,size = 4;
BYTE	Value[4]; 

	//Open or Create Key
	ret = RegCreateKeyEx(Hive, m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_QUERY_VALUE, &m_secu_atri, &m_key_handle,NULL);
	
	if(ret==ERROR_SUCCESS)
	{
		//Get Value
		ret = RegQueryValueEx(m_key_handle,ValueName ,NULL,NULL,Value,&size);

		if(ret==ERROR_SUCCESS)
		{
			//Close
			RegCloseKey(m_key_handle);
			*pvalue = *(DWORD*)Value;
			return true;
		}else{
			WriteLog("Cannot read Registry value (DWORD)");
			return false;
		}
	}else{
		WriteLog("Cannot read Registry key (DWORD)");
		return false;
	}
}
//-------------------------------------------------------------------------------------------
bool CMyRegistry::RegGet(HKEY Hive,char* ValueName,char* chrval,DWORD size,DWORD* len)
{//CHAR
char*	reserve;
DWORD	ret;
	reserve = chrval;
	
	//Open or Create Key
	ret = RegCreateKeyEx(Hive, m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_QUERY_VALUE, &m_secu_atri, &m_key_handle,NULL);

	if(ret==ERROR_SUCCESS)
	{
		//Get Value
		ret = RegQueryValueEx(m_key_handle,ValueName ,NULL,NULL,(BYTE*)chrval,&size);
		*len = size;

		if(ret==ERROR_SUCCESS)
		{
			if(*len>=3)
			{
				RegCloseKey(m_key_handle);
				chrval = reserve;
				ret = 0;
				return true;
			}else{//Empty value
				RegCloseKey(m_key_handle);
				chrval = reserve;
				return false;
			}
		}else{
			RegCloseKey(m_key_handle);
			chrval = reserve;
			m_ex.err = true;
			WriteLog("Cannot read Registry value (STRING)");
			return false;
		}
	}else{
		chrval = reserve;
		m_ex.err = true;
		WriteLog("Cannot read Registry key (STRING)");
		return false;
	}
}
//-------------------------------------------------------------------------------------------
bool CMyRegistry::RegSet(HKEY Hive,char* ValueName,DWORD Value)
{//DWORD
DWORD	ret;
	//Open or Create Key
	ret = RegCreateKeyEx(Hive,m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &m_secu_atri, &m_key_handle,NULL);

	if(ret==ERROR_SUCCESS)
	{
		//Set Value
		ret = RegSetValueEx(m_key_handle,ValueName,0,REG_DWORD,(LPBYTE)&Value, sizeof(Value));
		if(ret==ERROR_SUCCESS)
		{
			//Close
			RegCloseKey(m_key_handle);
			ret = 0;
			return true;
		}else{
			RegCloseKey(m_key_handle);
			WriteLog("Cannot write Registry value (DWORD)");
			m_ex.err = true;
			return false;
		}
	}
	else
	{
		WriteLog("Cannot write Registry key (DWORD)");
		m_ex.err = true;
		return false;
	}
}
//-------------------------------------------------------------------------------------------
bool CMyRegistry::RegSet(HKEY Hive,char* ValueName,char* Value,DWORD size)
{//CHAR
DWORD	ret;
	//Open or Create Key
	ret = RegCreateKeyEx(Hive,m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &m_secu_atri, &m_key_handle,NULL);

	if(ret==ERROR_SUCCESS)
	{
		//Set Value
		ret = RegSetValueEx(m_key_handle,ValueName,0,REG_SZ,(LPBYTE)Value, size);

		if(ret==ERROR_SUCCESS)
		{
			RegCloseKey(m_key_handle);
			ret = 0;
			return true;
		}else{
			RegCloseKey(m_key_handle);
			m_ex.err = true;
			WriteLog("Cannot write Registry value (STRING)");
			return false;
		}
	}
	else
	{
		WriteLog("Cannot write Registry key (STRING)");
		m_ex.err = true;
		return false;
	}
}
//-----------------------------------------------------------------------------------------------
bool CMyRegistry::RegSetBinary(HKEY Hive,char* ValueName,BYTE* Value,DWORD size)
{//BINARY
DWORD	ret;
	//Open or Create Key
	ret = RegCreateKeyEx(Hive,m_reg_key,NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_WRITE, &m_secu_atri, &m_key_handle,NULL);

	if(ret==ERROR_SUCCESS)
	{
		//Set Value
		ret = RegSetValueEx(m_key_handle,ValueName,0,REG_BINARY,Value, size);
		if(ret==ERROR_SUCCESS)
		{
			//Close
			RegCloseKey(m_key_handle);
			ret = 0;
			return true;
		}else{
			RegCloseKey(m_key_handle);
			m_ex.err = true;
			WriteLog("Cannot write Registry value (BINARY)");
			return false;
		}
	}
	else
	{
		m_ex.err = true;
		WriteLog("Cannot write Registry key (BINARY)");
		return false;
	}

}
//-----------------------------------------------------------------------------------------------
bool CMyRegistry::RegGetBinary(HKEY Hive,char* ValueName,BYTE* binval,DWORD size)
{//BINARY
BYTE* reserve;
DWORD	ret;
	reserve = binval;
	
	//Open or Create Key
	ret = RegCreateKeyEx(Hive, m_reg_key,NULL,NULL,
		REG_OPTION_NON_VOLATILE,KEY_QUERY_VALUE, &m_secu_atri, &m_key_handle,NULL);

	if(ret==ERROR_SUCCESS)
	{
		//Get Value
		ret = RegQueryValueEx(m_key_handle,ValueName ,NULL,NULL,binval,&size);

		if(ret==ERROR_SUCCESS)
		{
			if(size!=1)
			{
				RegCloseKey(m_key_handle);
				binval = reserve;
				ret = 0;
				return true;
			}else{//Empty value
				RegCloseKey(m_key_handle);
				binval = reserve;
				return false;
			}
		}else{
		
			RegCloseKey(m_key_handle);
			binval = reserve;
			m_ex.err = true;
			WriteLog("Cannot read Registry value (BINARY)");
			return false;
		}
	}else{
		binval = reserve;
		m_ex.err = true;
		WriteLog("Cannot read Registry key (BINARY)");
		return false;
	}
}


