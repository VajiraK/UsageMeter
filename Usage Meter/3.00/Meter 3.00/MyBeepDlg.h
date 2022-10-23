// MyBeepDlg.h: interface for the CMyBeepDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYBEEPDLG_H__E7A16B93_7727_4125_86BF_E8BBDA873896__INCLUDED_)
#define AFX_MYBEEPDLG_H__E7A16B93_7727_4125_86BF_E8BBDA873896__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyGlobal.h"
#include "MyRegistry.h"

class CMyBeepDlg : public CMyRegistry  
{
public:
	void SetCountersBeep();
			CMyBeepDlg();
	virtual ~CMyBeepDlg();
	void	TestBeep();
	void	RetrieveBeep();
	void	StartUp();
	void	TabChanged(LPARAM lParam);
	void	Initialize(MY_BEEP_STRUCT *pwinbeep, MY_BEEP_STRUCT *pintbeep,HWND me = NULL);
	bool	SaveBeep();

	MY_BEEP_STRUCT	*m_pwin_beep, *m_pint_beep;

private:
	bool	CheckInputs(bool silent=false);
	void	SetUpWindow();
	HFONT	CreateFont(char* face,WORD len,WORD size);
	
	MY_BEEP_STRUCT	m_beep_arr[2];
	HWND			m_me;
	HFONT			m_font_tab;
	BYTE			m_sel_tab;
};

#endif // !defined(AFX_MYBEEPDLG_H__E7A16B93_7727_4125_86BF_E8BBDA873896__INCLUDED_)
