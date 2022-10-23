// MyListView.h: interface for the CMyListView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLISTVIEW_H__916B904B_6865_4D13_B1CD_7080D54812EE__INCLUDED_)
#define AFX_MYLISTVIEW_H__916B904B_6865_4D13_B1CD_7080D54812EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyListView  
{
private:
	LVITEM m_li;
public:

	void SetupListview(HWND hwinList,HWND hintList,HFONT hwinfont,HFONT hintfont);
	void InsertRow(WORD index,char* lon_num,IU_FILE_STRUCT* us,char* user_name);
	void InsertTotal(WORD index,HWND hList,char* total);
	void DrawList(HWND hList,BOOL enable);
	void DeleteAll(HWND hList);
	virtual ~CMyListView();
	CMyListView();

	HWND	m_hlistview;
};

#endif // !defined(AFX_MYLISTVIEW_H__916B904B_6865_4D13_B1CD_7080D54812EE__INCLUDED_)
