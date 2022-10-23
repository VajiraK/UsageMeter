// MyLogFile.cpp: implementation of the CMyLogFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Usage Meter.h"
#include "MyLogFile.h"
#include "MyListView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define	IU_FILE_SRT_SIZE	48
#define TYPE_WINDOWS		0
#define TYPE_INTERNET		1

///////////////////////////////////////////////////////////////////////////////////////
void CMyLogFile::IntLogFileObj(HWND hint_list,HWND hwin_list,char* pint_total,char* pwin_total,CWnd* pmaindlg,DWORD* pprivilage)
{
	
	m_us.day[2]			= '\0';
	m_us.start_end[21]	= '\0';
	m_us.duration[8]	= '\0';
	m_us.roughdu[8]		= '\0';

	m_pint_total= pint_total;
	m_pwin_total= pwin_total;
	m_hint_list	= hint_list;
	m_hwin_list	= hwin_list;
	m_pmaindlg	= pmaindlg;
	CMyLogFolder::m_pprivilage = pprivilage; 
	m_pmythread	= AfxGetApp();
	MonthChange();
}
///////////////////////////////////////////////////////////////////////////////////////
bool CMyLogFile::LoadLog()
{
CFile	LF;
DWORD	filelenth;
char*	filedata = NULL;
char	buffer[255];
CString logpath;
CMyListView		list;
CFileException	ex;
	
	m_pmythread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);
	
	//Get loging path
	if(GetLogFolder(&logpath)==false)
		return false;
	else//m_logfilename set from IntLogFileObj by MonthChange
		logpath = logpath + m_logfilename;

	if(LF.Open(logpath,CFile::modeRead)!=1)
	{//File can't open so create it
		if(LF.Open(logpath,CFile::modeRead|CFile::modeCreate,&ex)!=1)
		{
			ex.GetErrorMessage(buffer,255);
			::MessageBox(m_pmaindlg->m_hWnd,buffer,"Usage Meter",MB_OK|MB_ICONSTOP);
			return false;//Still error occurs lets stop this
		}
	}
	filelenth = LF.GetLength();
	if(filelenth==0)
	{//file has no data
		list.DeleteAll(m_hwin_list);
		list.DeleteAll(m_hint_list);
		m_pmythread->SetThreadPriority(THREAD_PRIORITY_NORMAL);
		return true;	
	}
	filedata = new char[filelenth];
	LF.Read(filedata,filelenth);
	LF.Close();

//********* Fill Lists ************************************************
int			win_total_sec=0;
int			int_total_sec=0;
int			win_ruf_total_sec=0;
int			int_ruf_total_sec=0;
int			int_index=0;
int			win_index=0;
int			*ptotal,*pruftotal,*pindex;
DWORD		p=0;
char		log_no[3];

	list.DrawList(m_hwin_list,FALSE);
	list.DrawList(m_hint_list,FALSE);
	list.DeleteAll(m_hwin_list);
	list.DeleteAll(m_hint_list);

do{
	//Fill structure
	memcpy(&m_us,filedata+p,IU_FILE_SRT_SIZE);
	
	//Get names*******************
	p = p+IU_FILE_SRT_SIZE;
	buffer[m_us.names_len] = '\0';
	memcpy(buffer,filedata+p,m_us.names_len);
	p = p+m_us.names_len;
	//Get names*******************

	//Filter records
	if(m_us.type == TYPE_INTERNET){
	list.m_hlistview = m_hint_list;
	int_index++;
	pindex=&int_index;
	ptotal=&int_total_sec;
	pruftotal=&int_ruf_total_sec;
	NumToString(log_no,int_index);
	}else{
	list.m_hlistview = m_hwin_list;
	win_index++;
	pindex=&win_index;
	ptotal=&win_total_sec;
	pruftotal=&win_ruf_total_sec;
	NumToString(log_no,win_index);}

	//Insert log
	list.InsertRow(*pindex,log_no,&m_us,buffer);

	//Calcutate total
	//TimeAddition(ptotal,m_us.duration);
	//Calcutate rough total
	TimeAddition(pruftotal,m_us.roughdu);

}while(p<filelenth);

	delete[] filedata;
	list.DrawList(m_hwin_list,TRUE);
	list.DrawList(m_hint_list,TRUE);
//********* Fill Lists ************************************************
	
	//set Totals
	//FormatTotal(m_pwin_total,win_total_sec);
	//FormatTotal(m_pint_total,int_total_sec);

	//set rough totals**************
	filedata = &buffer[1];
	FormatTotal(filedata+1,win_ruf_total_sec);
	//set Total
	FormatTotal(m_pwin_total,win_ruf_total_sec);
	
	filedata[0] = '<';filedata[10] = '>';filedata[11] = '\0';
	list.InsertTotal(win_index,m_hwin_list,filedata);

	FormatTotal(filedata+1,int_ruf_total_sec);
	FormatTotal(m_pint_total,int_ruf_total_sec);

	list.InsertTotal(int_index,m_hint_list,filedata);
	//set rough totals**************

	m_pmythread->SetThreadPriority(THREAD_PRIORITY_NORMAL);
	return true;
}
//------------------------------------------------------------------------------------------------
bool CMyLogFile::Save_Int_Usage(DAY_STRUCT* day,char* start,char* end,char* duration,char* roughdu)
{//Save internet usage to the Log file

	m_us.type = TYPE_INTERNET;
	memcpy(m_us.day,day->day,2);

char st_en[22];
	memcpy(st_en,start,8);
	memcpy(st_en+8,"  -  ",5);
	memcpy(st_en+13,end,9);
	memcpy(m_us.start_end,st_en,22);

	memcpy(m_us.duration, duration,9);
	memcpy(m_us.roughdu, roughdu,9);
	//Get user list and lenth
char	users[200];
DWORD	size = 200;
		GetIntUsers(users,&size);
		m_us.names_len = size;
bool	ret = SaveLog(users);

	if(ret==true)
	{//reload log file
		LoadLog();
		return true;
	}else
		return false;
}
//------------------------------------------------------------------------------------------------
bool CMyLogFile::Save_Win_Usage(DAY_STRUCT* day,char* start,char* end,char* duration,char* roughdu)
{//Save windows usage to the Log file

	m_us.type = TYPE_WINDOWS;
	memcpy(m_us.day, day, 1);

char st_en[22];
	memcpy(st_en,start,8);
	memcpy(st_en+8,"  -  ",5);
	memcpy(st_en+13,end,9);
	memcpy(m_us.start_end,st_en,22);

	memcpy(m_us.duration, duration,9);
	memcpy(m_us.roughdu, roughdu,9);

char users[100];
	m_us.names_len = 100;
	GetWinUsers(users,&m_us.names_len);

	return SaveLog(users);
}
//------------------------------------------------------------------------------------------------
bool CMyLogFile::SaveLog(char* names)
{
CString logpath;
CFile	LF;
char	errmsg[255];
CFileException ex;

	//get logging folder from the registry
	if(GetLogFolder(&logpath)==true)
		logpath = logpath + m_logfilename;
	else
		return false;

	if(LF.Open(logpath,CFile::modeWrite)!=1)
		if(LF.Open(logpath,CFile::modeWrite|CFile::modeCreate)!=1)
		{//Connot open or create file
			ex.GetErrorMessage(errmsg,255);
			::MessageBox(m_pmaindlg->m_hWnd,errmsg,"Usage Meter",MB_OK|MB_ICONSTOP);
			return false;
		}

	//Goto the end of the file
	LF.Seek((UINT)0,CFile::end);

char*	buff=NULL;
DWORD	l;
	l = IU_FILE_SRT_SIZE + m_us.names_len;
	buff = new char[l];
	memcpy(buff,&m_us,IU_FILE_SRT_SIZE);
	memcpy(buff+IU_FILE_SRT_SIZE,names,m_us.names_len);
	LF.Write(buff,l);
	LF.Close();
	delete[] buff;
	return true;
}
//------------------------------------------------------------------------------------------------
CString	CMyLogFile::CreateTitle()
{
CString title;
	title = NumToMothname(GetSystemMonth());
	//File name set's here
	m_logfilename = title;
	#ifdef _DEBUG
	title = "Usage Meter Debug (" + title + ")";
	#else
	title = "Usage Meter (" + title + ")";
	#endif
return title;
}
//------------------------------------------------------------------------------------------------
void CMyLogFile::MonthChange()
{
	m_pmaindlg->SetWindowText(CreateTitle());
	m_logfilename = m_logfilename + ".iuf";
}
//--------------------------------------------------------------------------------------------------------
void CMyLogFile::FormatTotal(char *buf, DWORD seconds)
{//Capacity <999:59:59
DWORD num,single,divid,index;
DWORD n[3];
	
	buf[3] = buf[6] = ':';

//Convert seconds to time
	n[0]		= seconds/3600;	//Hourse
	seconds		= seconds%3600; //Reminder
	n[1]		= seconds/60;	//Minutes
	n[2]		= seconds%60;	//Reminder(That's seconds)

for(int t=0;t<=2;t++)
{//Loop through three time components
	//Get each components
	num = n[t];

	if(t==0)
	{//Hour part can be > 59 so deferent algo
		for(int i=0;i<=2;i++)
		{
			switch (i)
			{
			case 0:
				divid=100;
				single = num/divid;
				break;
			case 1:
				divid=10;
				num = single;
				single = num/divid;
				break;
			}

			switch (single)
			{
			case 0:
				buf[i]='0';single = num;break;
			case 1:
				buf[i]='1';single=num-1*divid;break;
			case 2:
				buf[i]='2';single=num-2*divid;break;
			case 3:
				buf[i]='3';single=num-3*divid;break;
			case 4:
				buf[i]='4';single=num-4*divid;break;
			case 5:
				buf[i]='5';single=num-5*divid;break;
			case 6:
				buf[i]='6';single=num-6*divid;break;
			case 7:
				buf[i]='7';single=num-7*divid;break;
			case 8:
				buf[i]='8';single=num-8*divid;break;
			case 9:
				buf[i]='9';single=num-9*divid;break;
			}
		}
	index = 4;
	}else{//Minuts and seconds always < 59

		for(int i=0;i<=1;i++)
		{
			if(i==0)
				single = num/10;

			switch (single)
			{
			case 0:
				buf[index]='0';single = num;break;
			case 1:
				buf[index]='1';single=num-1*10;break;
			case 2:
				buf[index]='2';single=num-2*10;break;
			case 3:
				buf[index]='3';single=num-3*10;break;
			case 4:
				buf[index]='4';single=num-4*10;break;
			case 5:
				buf[index]='5';single=num-5*10;break;
			case 6:
				buf[index]='6';single=num-6*10;break;
			case 7:
				buf[index]='7';single=num-7*10;break;
			case 8:
				buf[index]='8';single=num-8*10;break;
			case 9:
				buf[index]='9';single=num-9*10;break;
			}
		index++;
		}
	index++;
	}
}
}
//--------------------------------------------------------------------------------------------------------
void CMyLogFile::SetStatusFile(WORD flag)
{
char	path[256];
DWORD	len=256;
HANDLE	fileh;

	RegGet(HKEY_LOCAL_MACHINE,"LogFolder",path,&len);

	if((flag==CLEAR_STATUS)||(flag==CONNECTED)||(flag==DISCONNECTED))
	{	memcpy(path+(len-2),"Connected\0",10);
		DeleteFile(path);
		memcpy(path+(len-2),"Disconnected\0",13);
		DeleteFile(path);
	}	

	if(flag==CONNECTED)
	{	memcpy(path+(len-2),"Connected\0",10);
		fileh=CreateFile(path,0,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		CloseHandle(fileh);
	}	

	if(flag==DISCONNECTED)
	{	memcpy(path+(len-2),"Disconnected\0",13);
		fileh=CreateFile(path,0,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		CloseHandle(fileh);
	}	
}
