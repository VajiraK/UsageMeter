// MyListView.cpp: implementation of the CMyListView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "usage meter.h"
#include "MyListView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyListView::CMyListView()
{
	m_li.mask = LVIF_TEXT;
	m_li.state = NULL;
	m_li.stateMask  = NULL;
	m_li.iImage = NULL;
	m_li.lParam = NULL;
	m_li.iIndent = 0;
	m_li.cchTextMax = 0;
}

CMyListView::~CMyListView()
{

}

void CMyListView::InsertRow(WORD index,char* lon_num,IU_FILE_STRUCT* us,char* user_name)
{
	index--;
	//Log Number
	m_li.iSubItem	= 0;
	m_li.iItem  = index;
	m_li.pszText	= lon_num;
	::SendMessage(m_hlistview,LVM_INSERTITEM,0,(LPARAM)&m_li);
	//Day
	m_li.iSubItem	= 1;
	m_li.pszText	= us->day;
	::SendMessage(m_hlistview,LVM_SETITEMTEXT,(WPARAM)index,(LPARAM)&m_li);
	//From To
	m_li.iSubItem	= 2;
	m_li.pszText	= us->start_end;
	::SendMessage(m_hlistview,LVM_SETITEMTEXT,(WPARAM)index,(LPARAM)&m_li);
	//Duration
	m_li.iSubItem	= 3;
	m_li.pszText	= us->duration;
	::SendMessage(m_hlistview,LVM_SETITEMTEXT,(WPARAM)index,(LPARAM)&m_li);
	//User
	m_li.iSubItem	= 4;
	m_li.cchTextMax	= us->names_len;
	m_li.pszText = user_name;
	::SendMessage(m_hlistview,LVM_SETITEMTEXT,(WPARAM)index,(LPARAM)&m_li);
	//Rough Duration
	m_li.iSubItem	= 5;
	m_li.pszText	= us->roughdu;
	::SendMessage(m_hlistview,LVM_SETITEMTEXT,(WPARAM)index,(LPARAM)&m_li);
}
//------------------------------------------------------------------------------
void CMyListView::DeleteAll(HWND hList)
{
	::SendMessage(hList,LVM_DELETEALLITEMS,0,0);
}
//------------------------------------------------------------------------------
void CMyListView::DrawList(HWND hList,BOOL enable)
{
	::SendMessage(hList,WM_SETREDRAW ,(WPARAM)enable,0);
}
//------------------------------------------------------------------------------
void CMyListView::InsertTotal(WORD index,HWND hList, char *total)
{
	//Log Number
	m_li.iSubItem	= 0;
	m_li.iItem  = index;
	m_li.pszText	= "";
	::SendMessage(hList,LVM_INSERTITEM,0,(LPARAM)&m_li);
	//Day
	m_li.iSubItem	= 5;
	m_li.pszText	= total;
	::SendMessage(hList,LVM_SETITEMTEXT,(WPARAM)index,(LPARAM)&m_li);
}
//------------------------------------------------------------------------------
void CMyListView::SetupListview(HWND hwinList,HWND hintList,HFONT hwinfont,HFONT hintfont)
{
HWND		htemp;
LVCOLUMN	lco;

	lco.mask = LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;
	lco.fmt = LVCFMT_CENTER;
    lco.cchTextMax = 0; 
    lco.iImage = 0;
    lco.iOrder = 0;

	::SendMessage(hwinList,WM_SETFONT,(WPARAM)hwinfont,MAKELPARAM(FALSE, 0));
	::SendMessage(hintList,WM_SETFONT,(WPARAM)hintfont,MAKELPARAM(FALSE, 0));

for(int i=0;i<=1;i++)
{
	if(i==0)
		htemp = hintList;
	else
		htemp = hwinList;
	//Set Font
	::SendMessage(htemp,LVM_SETTEXTCOLOR,0,(LPARAM)RGB(0,0,255));
	//Set Extended styles
	::SendMessage(htemp,LVM_SETEXTENDEDLISTVIEWSTYLE,(WPARAM)LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT,(LPARAM)LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	//Prepair colunms
	lco.pszText = "Log";lco.cx = 40; 
	::SendMessage(htemp,LVM_INSERTCOLUMN,(WPARAM)1,(LPARAM)&lco);
	lco.pszText = "Day";lco.cx = 40; 
	::SendMessage(htemp,LVM_INSERTCOLUMN,(WPARAM)2,(LPARAM)&lco);
	lco.pszText = "From To";lco.cx = 145; 
	::SendMessage(htemp,LVM_INSERTCOLUMN,(WPARAM)3,(LPARAM)&lco);
	lco.pszText = "Duration";lco.cx = 80; 
	::SendMessage(htemp,LVM_INSERTCOLUMN,(WPARAM)4,(LPARAM)&lco);
	lco.pszText = "User(s)";lco.cx = 160;lco.fmt = LVCFMT_LEFT;
	::SendMessage(htemp,LVM_INSERTCOLUMN,(WPARAM)5,(LPARAM)&lco);
	lco.pszText = "Rough Duration";lco.cx = 105; ;lco.fmt = LVCFMT_CENTER;
	::SendMessage(htemp,LVM_INSERTCOLUMN,(WPARAM)6,(LPARAM)&lco);
	//Move ListView
	::MoveWindow(htemp,12,35,486,442,FALSE);
}
	

}

