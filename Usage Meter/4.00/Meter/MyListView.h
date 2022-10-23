// MyListView.h: interface for the CMyListView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLISTVIEW_H__E963E2BA_B6F8_455C_91AE_81658AD27283__INCLUDED_)
#define AFX_MYLISTVIEW_H__E963E2BA_B6F8_455C_91AE_81658AD27283__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <commctrl.h>
#include "MyString.h"

class CMyListView  : public CMyString
{
public:

			CMyListView();
	virtual ~CMyListView();
	void	SetupListview();
	void	InsertRow(MY_FILE_STRUCT* us);
	void	DrawList(BOOL enable);
	void	DeleteAll();

	DWORD	count;
	HWND	m_hlist;
	HFONT	m_hfont;

private:
	LVITEM	m_ls;

};

#endif // !defined(AFX_MYLISTVIEW_H__E963E2BA_B6F8_455C_91AE_81658AD27283__INCLUDED_)
