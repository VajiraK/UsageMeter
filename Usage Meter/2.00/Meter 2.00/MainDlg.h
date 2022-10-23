
#if !defined(AFX_MAINDLG_H__96E11F88_523A_4147_9E48_88B541251266__INCLUDED_)
#define AFX_MAINDLG_H__96E11F88_523A_4147_9E48_88B541251266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyServerPort.h"
#include "MyCounter.h"

// CMainDlg dialog
class CMainDlg : public CDialog
{
// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_USAGEMETER_DIALOG };
	CStatic		m_status_lbl;
	CTabCtrl	m_Tab_Ctrl;
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnFileViewer();
	afx_msg void OnBeepSet();
	#ifdef _DEBUG
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//********************** CUSTOM ******************************	
private:
	//Variables
	char	m_temp_duration[9];
	char	m_win_str_time[9];
	char	m_int_str_time[9];
	char	m_res_zerotime[9];
	char	m_temp_rugh_dura[9];
	char	m_now[9];
	char	m_res_tip_text[106];
	char	m_res_label_text[135];
	char	*m_win_duration,*m_int_duration;
	char	*m_win_total,*m_int_total;
	int		m_select_tab;
	int		m_win_str_sec, m_int_str_sec;
	HWND	m_hint_list, m_hwin_list;
	CWnd*	m_about_dlg;
	DWORD	m_privilage;
	CMenu*	m_pop_menu;
	HFONT	m_font_win, m_font_int;
	CMyCounter		m_win_counter,m_int_counter;
	CMyServerPort	m_my_api;
	//Functions
	#ifdef _DEBUG
		bool	Fake_Connection();
	#endif
		void	KillMeter();
		DWORD	FindLatsSlash(char *path,DWORD len);
inline	void	SetTip(int mode,int prayority);
inline	void	SetLable(int mode);
		void	SetUpTray(DWORD Task,char* tip,int size);
		void	SetBeep(bool reset_int_count, bool reset_win_count);
		void	StartUp();
		void	TimerMain();
		void	ShutDown();
		void	SetUpDialog();
		void	SaveWindowPos();
		void	ShowAboutBox();
		void	GetAppPath(char* path,DWORD* size, bool writerunkey);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__96E11F88_523A_4147_9E48_88B541251266__INCLUDED_)
