// MyLogFile.cpp: implementation of the CMyLogFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Usage Meter.h"
#include "MyLogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////////////////////////////////////////////
void CMyLogFile::IntLogFileObj(CListCtrl* pint_list,CListCtrl* pwin_list,CString* pint_total,CString* pwin_total,CWnd* pmaindlg)
{
	m_pint_total= pint_total;
	m_pwin_total= pwin_total;
	m_pint_list	= pint_list;
	m_pwin_list	= pwin_list;
	m_pmaindlg	= pmaindlg;
	m_pmythread	= AfxGetApp();
}
///////////////////////////////////////////////////////////////////////////////////////
void CMyLogFile::LoadLog()
{
CFile	LF;
long	lenth;
char*	temp;
CString log_data;
	
	m_pmythread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);

	if(LF.Open(m_logpath,CFile::modeRead)!=1)
	{//File can't open so create it
		LF.Open(m_logpath,CFile::modeRead|CFile::modeCreate);
	}
	lenth = (long)LF.GetLength();
	temp = new char[lenth+1];
	ZeroMemory(temp,lenth+1);
	LF.Read(temp,lenth);
	LF.Close();
	log_data.Insert(0,temp);
	delete[] temp;

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
	Format_Seconds(win_total_sec,m_pwin_total);
	Format_Seconds(int_total_sec,m_pint_total);

	m_pmythread->SetThreadPriority(THREAD_PRIORITY_NORMAL);
}
//------------------------------------------------------------------------------------------------
void CMyLogFile::SetLogPath()
{//getsystem month and set path
DWORD sys_mon = GetSystemMonth();
CString m = NumToMothname(sys_mon);

	#ifdef _DEBUG
	m_logpath="E:\\Usage Log\\";
	#else
	m_logpath="E:\\Usage Log\\";
	#endif

	m_logpath = m_logpath + m + ".iuf";
	//set caption
	m_pmaindlg->SetWindowText(CreateTitle());
}
//------------------------------------------------------------------------------------------------
void CMyLogFile::Save_Int_Usage(CString day,CString start,CString end,CString duration)
{//Save internet usage to the Log file
CFile	LF;
CString data = 'I'+day+'#'+start+"  -  "+end+'#'+duration+'#'+GetIntUsers()+'?';
int		lenth = data.GetLength();
	
	if(LF.Open(m_logpath,CFile::modeWrite)!=1)
	{//File can't open so create it
		LF.Open(m_logpath,CFile::modeWrite|CFile::modeCreate);
	}
	//Goto the end of the file
	LF.Seek((UINT)0,CFile::end);
	LF.Write(data.GetBuffer(lenth),lenth);
	LF.Close();
	//reload log file
	LoadLog();
}
//------------------------------------------------------------------------------------------------
void CMyLogFile::Save_Win_Usage(CString day,CString start,CString end,CString duration)
{//Save windows usage to the Log file
CFile LF;
CFileException ex;
CString temp;
	temp = 'W'+day+'#'+start+"  -  "+end+'#'+duration+'#'+GetWinUsers()+'?';
	if(LF.Open(m_logpath,CFile::modeWrite)!=1)
	{//File can't open so create it
		LF.Open(m_logpath,CFile::modeWrite|CFile::modeCreate);
	}
	
	//Goto the end of the file
	LF.Seek((UINT)0,CFile::end);
	int lenth = temp.GetLength();
	LF.Write(temp.GetBuffer(lenth),lenth);
	LF.Close();
}
//------------------------------------------------------------------------------------------------
CString CMyLogFile::CreateTitle()
{
CString title;	
	title = NumToMothname(GetSystemMonth());
	#ifdef _DEBUG
	title = "Usage Meter Debug (" + title + ")";
	#else
	title = "Usage Meter (" + title + ")";
	#endif
	return title;
}
//------------------------------------------------------------------------------------------------

