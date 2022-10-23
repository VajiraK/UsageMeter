// MyLogFile.cpp: implementation of the CMyLogFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "file viewer.h"
#include "MyLogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CMyLogFile::IntLogFileObj(CListCtrl *pint_list,CListCtrl *pwin_list,CStatic *pintlable,CStatic *pwinlable,CWnd *pmaindlg)
{
	m_pmythread	= AfxGetApp();
	m_pint_list	= pint_list;
	m_pwin_list	= pwin_list;
	m_int_lable	= pintlable;
	m_win_lable	= pwinlable;
	m_pmaindlg	= pmaindlg;	
}
//----------------------------------------------------------------------------------
void CMyLogFile::LoadLogFile(CString path)
{
CFile	LF;
long	lenth;
char*	temp;
CString log_data;
	
	m_pmythread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);

	if(LF.Open(path,CFile::modeRead)!=1)
	{//File can't open so create it
		LF.Open(path,CFile::modeRead|CFile::modeCreate);
	}
	lenth = (long)LF.GetLength();
	temp = new char[lenth+1];
	ZeroMemory(temp,lenth+1);
	LF.Read(temp,lenth);
	LF.Close();
	log_data.Insert(0,temp);
	delete temp;

//Split Data
CStringArray records;
	Split(&log_data,&records,'?');

//********* Fill Lists ************************************************
int		win_total_sec, int_total_sec;
int*	ptotal;
int		arr_index;
int		int_index=0;
int		win_index=0;
int*	pindex;

CStringArray	items;
CString			log_no;
CListCtrl*		plist;
	
	win_total_sec = 0; 
	int_total_sec = 0;

	m_pint_list->SetRedraw(FALSE);
	m_pwin_list->SetRedraw(FALSE);
	m_pint_list->DeleteAllItems();
	m_pwin_list->DeleteAllItems();

for(arr_index=0;arr_index<=records.GetUpperBound();arr_index++)
{
	//Split records(Eg - "I05#00:34:52 - 23:34:45#45:34:12#LokkA")
	Split(&records.GetAt(arr_index),&items,'#');

	//Filter records
	if(items.GetAt(0).Left(1)=='I'){
	plist=m_pint_list;
	int_index++;
	pindex=&int_index;
	ptotal=&int_total_sec;
	log_no.Format("%i",int_index);
	} else{
	plist=m_pwin_list;
	win_index++;
	pindex=&win_index;
	ptotal=&win_total_sec;
	log_no.Format("%i",win_index);}

	//Log number
	plist->InsertItem(*pindex-1,log_no.GetBuffer(log_no.GetLength()));
	//Day
	plist->SetItemText(*pindex-1,1,items.GetAt(0).Right(2));
	//From To
	plist->SetItemText(*pindex-1,2,items.GetAt(1));
	//Duration
	plist->SetItemText(*pindex-1,3,items.GetAt(2));

	//Calcutate total
	TimeAddition(ptotal,items.GetAt(2).GetBuffer(8));

	//User name
	plist->SetItemText(*pindex-1,4,items.GetAt(3));
	
	items.RemoveAll();
}
	m_pint_list->SetRedraw(TRUE);
	m_pwin_list->SetRedraw(TRUE);
//********* Fill Lists ************************************************
	//set Totals
	//Format_Seconds(win_total_sec,m_pwin_total);
	Format_Seconds(int_total_sec,&m_totals);
	m_totals = "Total Internet Usage - " + m_totals;
	m_int_lable->SetWindowText(m_totals.GetBuffer(31));
	m_totals.Empty();
	Format_Seconds(win_total_sec,&m_totals);
	m_totals = "Total Windows Usage - " + m_totals;
	m_win_lable->SetWindowText(m_totals.GetBuffer(30));

	//Set Dlg Title
int len = path.GetLength();
	arr_index = FindLatsSlash(&path);
	path = path.Right(len-arr_index-1);
	len = path.GetLength();
	path = path.Left(len-4);

	if(GetThisMonth()==path)
	path = "File Viewer (" + path.Left(len-4) + ") This Month";
	else
	path = "File Viewer (" + path.Left(len-4) + ")";

	m_pmaindlg->SetWindowText(path);
	
	m_pmythread->SetThreadPriority(THREAD_PRIORITY_NORMAL);
}
//----------------------------------------------------------------------------------
void CMyLogFile::Split(CString* data,CStringArray* arr,char delemiter)
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
//----------------------------------------------------------------------------------
#define TH		0
#define TM		1
#define TS		2
void CMyLogFile::TimeAddition(int* total_seconds,char* add_time)
{//time recive like "12:45:34"
//More efficient function to convert time component to Int(eg - 23:45:56)
int itime[3];
int values[2];
int index;
char* com;

	index=0;

		for(int y=0;y<8;y=y+3)
		{//Loop though one time (23:45:34)
		com = add_time+y;
		//initialize
		itime[index]=0;
			for(int i=0;i<2;i++)
			{//Convert one time componemt (23)
				switch (com[i])
				{
				case '0':
					values[i]=0;break;
				case '1':
					values[i]=1;break;
				case '2':
					values[i]=2;break;
				case '3':
					values[i]=3;break;
				case '4':
					values[i]=4;break;
				case '5':
					values[i]=5;break;
				case '6':
					values[i]=6;break;
				case '7':
					values[i]=7;break;
				case '8':
					values[i]=8;break;
				case '9':
					values[i]=9;break;
				}
				//Tenth place
				if(i==0)
					values[0]=values[0]*10;
				itime[index]=itime[index]+values[i];
			}
		index++;
		}

	//End time convert to seconds
	itime[TM] = itime[TM] * 60;
	itime[TM] = itime[TM] + itime[TS];
	itime[TH] = itime[TH] * 3600;
	itime[TH] = itime[TH] + itime[TM];

	//add seconds
	*total_seconds = *total_seconds + itime[TH];
}
//--------------------------------------------------------------------------------------------
void CMyLogFile::Format_Seconds(int seconds, CString *time)
{
int S,M,H;
//Convert seconds to time
	H		= seconds/3600;	//Hourse
	seconds	= seconds%3600; //Reminder
	M		= seconds/60;	//Minutes
	S		= seconds%60;	//Reminder(That's seconds)
//Convert seconds to time

//Format output
	if(S<=9){sS.Format("%c%i",'0',S);} else
	{sS.Format("%i",S);}

	if(M<=9){sM.Format("%c%i",'0',M);} else
	{sM.Format("%i",M);}

	if(H<=9){sH.Format("%c%i",'0',H);} else
	{sH.Format("%i",H);}

	time->Format("%s:%s:%s",sH,sM,sS);
}
//--------------------------------------------------------------------------------------------
void CMyLogFile::AssosiateFiles()
{
SECURITY_ATTRIBUTES sa;
HKEY				hKey;
CString				apppath;
DWORD				len;

	sa.nLength=sizeof(sa);
	sa.bInheritHandle=1;
	sa.lpSecurityDescriptor=NULL;

	apppath = GetAppPath();
	len		= apppath.GetLength();

	RegCreateKeyEx(HKEY_CLASSES_ROOT,".iuf",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	RegSetValueEx(hKey,NULL,0,REG_SZ,(LPBYTE)"usagemeterfile", 14);
	RegCloseKey(hKey);

	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	RegSetValueEx(hKey,NULL,0,REG_SZ,(LPBYTE)"Usage Meter Log File", 20);
	RegSetValueEx(hKey,"NeverShowExt",0,REG_SZ,(LPBYTE)"", 0);
	RegCloseKey(hKey);
	//DefaultIcon
	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile\\DefaultIcon",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	RegSetValueEx(hKey,NULL,0,REG_SZ,(LPBYTE)apppath.GetBuffer(len), len);
	RegCloseKey(hKey);
	//Open command
	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile\\shell",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	RegCloseKey(hKey);
	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile\\shell\\Open",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	RegCloseKey(hKey);
	RegCreateKeyEx(HKEY_CLASSES_ROOT,"usagemeterfile\\shell\\Open\\command",NULL,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, &sa, &hKey,NULL);
	apppath = apppath + " %1";
	len = len + 3;
	RegSetValueEx(hKey,NULL,0,REG_SZ,(LPBYTE)apppath.GetBuffer(len), len);
	RegCloseKey(hKey);
}
//--------------------------------------------------------------------------------------------
CString CMyLogFile::GetAppPath()
{
char path[100];
	GetModuleFileName(NULL,path,100);
	return path;
}
//----------------------------------------------------------------------------------
CString CMyLogFile::GetThisMonth()
{
SYSTEMTIME ST;

	::GetSystemTime(&ST);

	switch(ST.wMonth)
	{
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	}
	return "ERROR";
}
//----------------------------------------------------------------------------------
int CMyLogFile::FindLatsSlash(CString *path)
{
char*	p;
int		len;
	len = path->GetLength()-1;
	p = path->GetBuffer(len);
	p=p+len;
	for(int i=len;i>0;i--)
	{
		if(*p=='\\')
			return i;
		p--;
	}
	return -1;
}
