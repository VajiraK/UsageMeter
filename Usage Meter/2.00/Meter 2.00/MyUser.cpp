// MyUser.cpp: implementation of the CMyUser class.

#include "stdafx.h"
#include "MyUser.h"

//----------------------------------------------------------------------------------
void CMyUser::GetCurrentUser(CString* user)
{//get current user name form windows
char	c[100];
DWORD	i=100;
	if(GetUserName(c,&i)!=0)
		*user = c;
	else
		*user = "Unknown";
}
//----------------------------------------------------------------------------------
void CMyUser::GetIntUsers(char* users,DWORD* size)
{//get reg saved user names
	RegGet(HKEY_LOCAL_MACHINE,"ActiveUsers",users,size);
}
//----------------------------------------------------------------------------------
void CMyUser::GetWinUsers(char* users,DWORD* len)
{//get reg saved user names
	RegGet(HKEY_LOCAL_MACHINE,"LogonUsers",users,len);
}
//----------------------------------------------------------------------------------
void CMyUser::AddUser()
{//add users to registry
CString		curuser,users,regusers;
CString*	userarr;
DWORD		size;
bool		ex_user=false;

//LOGON USERS***************************
	//get user list from registry
char	czusers[100];
	size = 100;
	RegGet(HKEY_LOCAL_MACHINE,"LogonUsers",czusers,&size);
	regusers = czusers;
	GetCurrentUser(&curuser);
	//check wether the user name already exist
	size = regusers.GetLength();
	userarr = Split(regusers.GetBuffer(size),',',&size,10);
	for(DWORD i=0;i<=size;i++)
	{
		if(userarr[i]==curuser)
		{
		ex_user = true;
		break;
		}
	}
	delete[] userarr;
	if(ex_user==false)
	{//nop add this user
		regusers = regusers  + ',' + curuser;
		size = regusers.GetLength();
		RegSet(HKEY_LOCAL_MACHINE,"LogonUsers",regusers.GetBuffer(size),size);
	}
//LOGON USERS****************************

//ACTIVE USERS***************************
	RegGet(HKEY_LOCAL_MACHINE,"ActiveUsers",czusers,&size);
	regusers = czusers;
	regusers = regusers  + ',' + curuser;
	size = regusers.GetLength();
	RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",regusers.GetBuffer(size),size);
//ACTIVE USERS***************************
}
//----------------------------------------------------------------------------------
void CMyUser::RemoveUser()
{
CString		regusers ,curuser;
CString*	userarr;
DWORD		size;
char		users[100];

	RegGet(HKEY_LOCAL_MACHINE,"ActiveUsers",users,&size);
	GetCurrentUser(&curuser);
	
	userarr = Split(users,',',&size,10);

	for(DWORD i=0;i<=size;i++)
	{
		if(userarr[i]!=curuser)
		{
			if(regusers.IsEmpty())
			regusers = userarr[i];
			else
			regusers = regusers + ',' + userarr[i];
		}
	}
	delete[] userarr;
size = regusers.GetLength();
	RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",regusers.GetBuffer(size),size);
}
//----------------------------------------------------------------------------------
void CMyUser::InitializeUserList()
{
CString name;
DWORD	size;
	GetCurrentUser(&name);
	size = name.GetLength();
	RegSet(HKEY_LOCAL_MACHINE,"LogonUsers",name.GetBuffer(size),size);
	RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",name.GetBuffer(size),size);
}
//----------------------------------------------------------------------------------
CString* CMyUser::Split(char *data, char delimit,DWORD* datalen,WORD arrsize)
{
DWORD		index,p,l,oi;
char		temp_arr[200];
CString*	strarr;

	//create dynamic string array
	strarr = new CString[arrsize];

	oi = index = 0;
	*datalen = *datalen-1;//Reduce one as zerobase index

	for(DWORD i=0;i<=*datalen;i++)
	{
		if(data[i]==delimit)
		{
			p = oi;
			l = i - oi;
			memcpy(temp_arr,data+p, l);
			temp_arr[l] = '\0';
			strarr[index++]=temp_arr;
			oi = i+1;
			if(index==arrsize)//Array should resize
				strarr = ExpandStrArr(strarr,&arrsize);
		}
	}
	//Final item
	memcpy(temp_arr,data+oi, i-oi);
	temp_arr[i-oi] = '\0';
	strarr[index]=temp_arr;

	//Return the number of eliments in the array by pointer
	if(index!=0)
		*datalen = index - 1;
	else
		*datalen = 0;
	//return array
	return strarr;
}
//----------------------------------------------------------------------------------
CString* CMyUser::ExpandStrArr(CString *str_arr,WORD* size)
{
CString* new_strarr;
	
	new_strarr = new CString[*size+100];
	*size = *size-1;

	for(int i=0;i<=*size;i++)
		new_strarr[i] = str_arr[i];

	//delete old array
	delete[] str_arr;
	*size = *size+101;
	return new_strarr;
}
