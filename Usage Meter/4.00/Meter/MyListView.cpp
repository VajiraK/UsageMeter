// MyListView.cpp: implementation of the CMyListView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyListView.h"

CMyListView::~CMyListView()
{
	DeleteObject(m_hfont);
}
//------------------------------------------------------------------------------------------------
CMyListView::CMyListView()
{
	m_ls.mask		= LVIF_TEXT;
	m_ls.state		= NULL;
	m_ls.stateMask  = NULL;
	m_ls.iImage		= NULL;
	m_ls.lParam		= NULL;
	m_ls.iIndent	= 0;
	m_ls.cchTextMax = 0;	
}
//------------------------------------------------------------------------------------------------
void CMyListView::InsertRow(MY_FILE_STRUCT* us)
{
char	temp[22];
BYTE	dtemp1[3],dtemp2[3],dtemp3[3];

	//Log Number
	m_ls.iSubItem	= 0;
	m_ls.iItem		= count+1;
	temp[3] = '\0';
	NumToString(temp, count+1,2);
	m_ls.pszText	= temp;
	SendMessage(m_hlist,LVM_INSERTITEM,0,(LPARAM)&m_ls);
	//Day
	temp[2] = '\0';
	NumToString(temp, us->day,1);
	m_ls.pszText	= temp;
	m_ls.iSubItem	= 1;
	SendMessage(m_hlist,LVM_SETITEMTEXT,(WPARAM)count,(LPARAM)&m_ls);
	//From To
		//Prepare buffer
		temp[21] = '\0';
		temp[2] = temp[5] = temp[15] = temp[18] = ':';
		memcpy(&temp[8],"  -  ",5);
		for(int i=0;i<=2;i++)
		{
			dtemp1[i]=us->start[i];
			dtemp2[i]=us->end[i];
			dtemp3[i]=us->duration[i];
		}
		MakeStrTime(temp, &dtemp1[0]);
		MakeStrTime(&temp[13], &dtemp2[0]);
	m_ls.pszText	= temp;
	m_ls.iSubItem	= 2;
	SendMessage(m_hlist,LVM_SETITEMTEXT,(WPARAM)count,(LPARAM)&m_ls);
	//Duration
	temp[8] = '\0';
	MakeStrTime(temp, &dtemp3[0]);
	m_ls.pszText	= temp;
	m_ls.iSubItem	= 3;
	SendMessage(m_hlist,LVM_SETITEMTEXT,(WPARAM)count,(LPARAM)&m_ls);
	//User
	us->users[us->users_len] = '\0';
	m_ls.pszText = us->users;
	m_ls.iSubItem	= 4;
	SendMessage(m_hlist,LVM_SETITEMTEXT,(WPARAM)count,(LPARAM)&m_ls);
	
	count++;
}
//------------------------------------------------------------------------------------------------
void CMyListView::SetupListview()
{
LVCOLUMN	lco;

	lco.mask		= LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;
	lco.fmt			= LVCFMT_CENTER;
    lco.cchTextMax	= lco.iImage = lco.iOrder = 0; 

	SendMessage(m_hlist,WM_SETFONT,(WPARAM)m_hfont,MAKELPARAM(FALSE, 0));
	//Set Font color
	SendMessage(m_hlist,LVM_SETTEXTCOLOR,0,(LPARAM)RGB(0,0,255));
	//Set Extended styles
	SendMessage(m_hlist,LVM_SETEXTENDEDLISTVIEWSTYLE,(WPARAM)LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT,(LPARAM)LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	//Prepair colunms
	lco.pszText = "Log";lco.cx = 45; 
	SendMessage(m_hlist,LVM_INSERTCOLUMN,(WPARAM)1,(LPARAM)&lco);
	lco.pszText = "Day";lco.cx = 50; 
	SendMessage(m_hlist,LVM_INSERTCOLUMN,(WPARAM)2,(LPARAM)&lco);
	lco.pszText = "From To";lco.cx = 155; 
	SendMessage(m_hlist,LVM_INSERTCOLUMN,(WPARAM)3,(LPARAM)&lco);
	lco.pszText = "Duration";lco.cx = 90; 
	SendMessage(m_hlist,LVM_INSERTCOLUMN,(WPARAM)4,(LPARAM)&lco);
	lco.pszText = "User(s)";lco.cx = 160;lco.fmt = LVCFMT_LEFT;
	SendMessage(m_hlist,LVM_INSERTCOLUMN,(WPARAM)5,(LPARAM)&lco);
}
//------------------------------------------------------------------------------
void CMyListView::DeleteAll()
{
	SendMessage(m_hlist,LVM_DELETEALLITEMS,0,0);
}
//------------------------------------------------------------------------------
void CMyListView::DrawList(BOOL enable)
{
	SendMessage(m_hlist,WM_SETREDRAW ,(WPARAM)enable,0);
}