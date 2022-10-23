// MyMainWnd.h: interface for the CMyMailWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMAILWND_H__96AC4ACA_EF70_4EDA_B2D7_A22E296783B4__INCLUDED_)
#define AFX_MYMAILWND_H__96AC4ACA_EF70_4EDA_B2D7_A22E296783B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyListView.h"
#include "MyServerPort.h"

class CMyMainWnd : public CMyServerPort
{
public:
				CMyMainWnd();
	virtual		~CMyMainWnd();
	void		MainTimerTicks();
	void		ComTimerTicks();
	void		StartUp();
	void		ShutDown(bool exit=false);
	void		TabChanged(LPARAM lParam);
	void		LaunchViewer();
			
	HANDLE		m_mutex;
	HINSTANCE	m_hinstance;
	HFONT		m_font_exep_edit;
	CMyListView m_int_list, m_win_list;
	CMyCounter	m_win_counter, m_int_counter;

private:

	HFONT	CreateFont(char* face,WORD len,WORD size);
	void	DeleteFonts();
	void	SetTip(int mode,int prayority);
	void	SetLable(int mode);
	void	SetUpWindow();
	void	SetUpTray(DWORD Task,char* tip,int size);
	void	KillMeter();
	void	SaveWindowPos();

	HWND		m_hlable_ctrl, m_htab_ctrl;
	HFONT		m_font_tab;
	HFONT		m_font_ok, m_font_beep, m_font_fview;
	HFONT		m_font_lable;
	char		m_res_tip_text[106];
	char		m_res_label_text[135];
	int			m_select_tab;

	#ifdef _DEBUG
	bool	Fake_Connection();
	#endif
};

#endif // !defined(AFX_MYMAILWND_H__96AC4ACA_EF70_4EDA_B2D7_A22E296783B4__INCLUDED_)
