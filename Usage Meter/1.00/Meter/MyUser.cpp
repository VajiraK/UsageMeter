// MyUser.cpp: implementation of the CMyUser class.

#include "stdafx.h"
#include "MyUser.h"

//////////////////////////////////////////////////////////////////////
CString CMyUser::GetCurrentUser()
{//get current user name form windows
CString name;
char	c[100];
DWORD	i=100;
	GetUserName(c,&i);
	name.Insert(0,c);
	return name;
}
//////////////////////////////////////////////////////////////////////
CString CMyUser::GetIntUsers()
{//get reg saved user names
CString names;
	RegGet(HKEY_LOCAL_MACHINE,"ActiveUsers",&names);
	return names;
}
//////////////////////////////////////////////////////////////////////
CString CMyUser::GetWinUsers()
{//get reg saved user names
CString names;
	RegGet(HKEY_LOCAL_MACHINE,"LogonUsers",&names);
	return names;
}
//////////////////////////////////////////////////////////////////////
void CMyUser::AddUser()
{//add users to registry
CString			curuser,users,regusers;
CStringArray	arr;
DWORD			size;
bool	ex_user=false;
//LOGON USERS***************************
	//get user list from registry
	RegGet(HKEY_LOCAL_MACHINE,"LogonUsers",&regusers);
	curuser = GetCurrentUser();
	//check wether the user name already exist
	Split(&regusers,&arr,',');
	for(int i=0;i<=arr.GetUpperBound();i++)
	{
		if(arr.GetAt(i)==curuser)
		{
		ex_user = true;
		break;
		}
	}
	if(ex_user==false)
	{//nop add this user
		regusers = regusers  + ',' + curuser;
		size = regusers.GetLength();
		RegSet(HKEY_LOCAL_MACHINE,"LogonUsers",regusers.GetBuffer(size),size);
	}
//LOGON USERS***************************

//ACTIVE USERS***************************

	RegGet(HKEY_LOCAL_MACHINE,"ActiveUsers",&regusers);
	regusers = regusers  + ',' + curuser;
	size = regusers.GetLength();
	RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",regusers.GetBuffer(size),size);
//ACTIVE USERS***************************
}
//////////////////////////////////////////////////////////////////////
void CMyUser::RemoveUser()
{
CString			regusers ,curuser;
CStringArray	arr;
DWORD			size;

	RegGet(HKEY_LOCAL_MACHINE,"ActiveUsers",&regusers);
	curuser = GetCurrentUser();
	Split(&regusers,&arr,',');
	regusers.Empty();

	for(int i=0;i<=arr.GetUpperBound();i++)
	{
		if(arr.GetAt(i)!=curuser)
		{
			if(regusers.IsEmpty())
			regusers = arr.GetAt(i);
			else
			regusers = regusers + ',' + arr.GetAt(i);
		}
	}

size = regusers.GetLength();
	RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",regusers.GetBuffer(size),size);
}
//////////////////////////////////////////////////////////////////////
void CMyUser::InitializeUserList()
{
CString name;
DWORD	size;
	name = GetCurrentUser();
	size = name.GetLength();
	RegSet(HKEY_LOCAL_MACHINE,"LogonUsers",name.GetBuffer(size),size);
	RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",name.GetBuffer(size),size);
}
//////////////////////////////////////////////////////////////////////
void CMyUser::Split(CString* data,CStringArray* arr,char delemiter)
{
static int data_lenth;
static int start;
static int end;
static int arr_index;
static int mid_lenth;
	
	start=end=arr_index=mid_lenth=0;
	arr->RemoveAll();

	end=data->Find(delemiter,0);
	mid_lenth=end;
	//Splitting
	while(end!=-1)
	{
		arr->SetAtGrow(arr_index,data->Mid(start,mid_lenth));
		start=end+1;
		end=data->Find(delemiter,start);
		mid_lenth=end-start;
		++arr_index;
	}
	//get last item
	data_lenth=data->GetLength();
	if(data_lenth!=start)
		arr->SetAtGrow(arr_index,data->Right(data_lenth-start));
}


