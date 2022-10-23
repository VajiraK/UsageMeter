// MyUser.cpp: implementation of the CMyUser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyUser.h"

CMyUser::CMyUser()
{}
CMyUser::~CMyUser()
{}
//----------------------------------------------------------------------------------------------
void CMyUser::SetLogonUsers()
{
	m_um_log.users_len = 250;

	if(RegGet(HKEY_LOCAL_MACHINE,"LogonUsers",m_users,m_um_log.users_len,&m_um_log.users_len)==false)
	{//Error
		WriteLog("Cannot get LogonUsers list!");
		m_um_log.users_len = 9;
		memcpy(m_users, "<Unknown>", m_um_log.users_len);
	}else{
		FormatUserList();
	}

	m_um_log.users = m_users;
}
//----------------------------------------------------------------------------------------------
void CMyUser::SetActiveUsers()
{
	m_um_log.users_len = 250;

	if(RegGet(HKEY_LOCAL_MACHINE,"ActiveUsers",m_users,m_um_log.users_len,&m_um_log.users_len)==false)
	{//Error
		//AddExeption("Cannot get ActiveUsers list!");
		m_um_log.users_len = 9;
		memcpy(m_users, "<Unknown>", m_um_log.users_len);
	}else{
		FormatUserList();
	}

	m_um_log.users = m_users;
}
//----------------------------------------------------------------------------------------------
void CMyUser::InitializeUserList()
{
	m_um_log.users_len = 250;
	GetUserName(m_users, &m_um_log.users_len);
	RegSet(HKEY_LOCAL_MACHINE,"LogonUsers",m_users, m_um_log.users_len);
	RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",m_users, m_um_log.users_len);
}
//----------------------------------------------------------------------------------------------
void CMyUser::AddUser()
{
char	regusers[250];
DWORD	reglen,userlen;
bool	ret;

//LogonUsers****************************************************************************
	reglen = 250;
	ret = RegGet(HKEY_LOCAL_MACHINE, "LogonUsers", regusers, reglen, &reglen);
	reglen--;
	
	m_um_log.users_len = 250;
	GetUserName(m_users, &m_um_log.users_len);
	m_um_log.users_len--;
	userlen = m_um_log.users_len;

	//Add current user
	if(ret==false)
	{//Some error (No user names from reg)
		memcpy(regusers, m_users, userlen);
		regusers[userlen] = '+';
		userlen++;
	}else{
		if(regusers[reglen-1]=='+')
		{//Reg got error free genuing users
			//Check wether the current user already exist in reg
			if(FindUser(regusers,m_users,(WORD)reglen,(WORD)userlen))
			{
				goto LOCATION_ONE;
			}else{
				memcpy(&regusers[reglen], m_users, userlen);
				userlen += reglen;
				regusers[userlen] = '+';
				userlen++;
			}
		}else{//Reg users must tail '+' if not there is a problem so re-initalize user list
			memcpy(regusers, m_users, userlen);
			regusers[userlen] = '+';
			userlen++;
		}
	}
	
	//Save result to reg
	regusers[userlen] = '\0';
	userlen++;
	if(RegSet(HKEY_LOCAL_MACHINE,"LogonUsers",regusers, userlen)==false)
	{
		//AddExeption("Cannot create LogonUsers list!");
	}
//LogonUsers****************************************************************************
LOCATION_ONE:
//ActiveUsers***************************************************************************
	reglen = 250;
	ret = RegGet(HKEY_LOCAL_MACHINE, "ActiveUsers", regusers, reglen, &reglen);
	reglen--;

	if(ret==false)
	{//Some error (No user names from reg)
		memcpy(regusers, m_users, m_um_log.users_len);
		regusers[m_um_log.users_len] = '+';
		m_um_log.users_len++;
	}else
	{//There are users in registry
		if(regusers[reglen-1]=='+')
		{//Reg got error free genuing users
			memcpy(&regusers[reglen], m_users, m_um_log.users_len);
			m_um_log.users_len += reglen;
			regusers[m_um_log.users_len] = '+';
			m_um_log.users_len++;
		}else{
			memcpy(regusers, m_users, m_um_log.users_len);
			regusers[m_um_log.users_len] = '+';
			m_um_log.users_len++;
		}
	}

	//Save result to reg
	regusers[m_um_log.users_len] = '\0';
	m_um_log.users_len++;
	if(RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",regusers, m_um_log.users_len)==false)
	{
		//AddExeption("Cannot create ActiveUsers list!");
	}
//ActiveUsers***************************************************************************
}
//----------------------------------------------------------------------------------------------
bool CMyUser::FindUser(char *list, char *user, WORD listlen, WORD userlen, WORD* srtpoint, WORD* endpoint)
{
WORD	srt,pielen;
char	piece[25];
bool	equal;

	srt		= 0;
	pielen	= 0;
	equal	= false;
	
		for(int a=0;a<=listlen;a++)
		{
			pielen++;

			if(list[a]=='+')
			{
			pielen--;
				if(pielen==userlen)
				{
					//Get current piece
					memcpy(piece,&list[a-pielen],pielen);
					//Compaire
					for(int b=0;b<=userlen-1;b++)
					{
						if(user[b]!=piece[b])
						{
							equal = false;
							break;
						}else{
							equal = true;
						}
					}
				}
			pielen = 0;
			}

			//Found equal one
			if(equal)
			{
				if(srtpoint!=NULL)
				{
					*srtpoint = (WORD)a - userlen;
					*endpoint  = *srtpoint + userlen +1;
					return true;
				}else
				{
					return true;
				}
			}
		}
	return false;
}
//---------------------------------------------------------------------------------------
void CMyUser::FormatUserList()
{	
	for(DWORD i=0;i<=m_um_log.users_len;i++)
	{
		if(m_users[i]=='+')
		{//Replace '+'
			m_users[i]= ',';
		}
	}
	//Cut last '+'
	m_um_log.users_len-=2;
}
//-----------------------------------------------------------------------------------------
void CMyUser::RemoveUser()
{
char	regusers[250];
DWORD	reglen;
WORD	srtpoint,endpoint;;
bool	ret;

	reglen = 250;
	ret = RegGet(HKEY_LOCAL_MACHINE, "ActiveUsers", regusers, reglen, &reglen);
	reglen--;
	
	if(ret)
	{
		if(regusers[reglen-1]=='+')
		{//Reg got error free genuing users
			//Get cur user from windows
			m_um_log.users_len = 250;
			GetUserName(m_users, &m_um_log.users_len);
			m_um_log.users_len--;
			//Fild cur user in reg list
			if(FindUser(regusers,m_users,(WORD)reglen,(WORD)m_um_log.users_len,&srtpoint,&endpoint))
			{//Found lets remove it
				memcpy(m_users, regusers, srtpoint);//Lionel+
				memcpy(&m_users[srtpoint], &regusers[endpoint], reglen-endpoint);
				reglen = srtpoint+(reglen-endpoint);
				//Save result
				m_users[reglen] = '\0';
				RegSet(HKEY_LOCAL_MACHINE,"ActiveUsers",m_users, reglen+1);
			}
		}
	}
}
