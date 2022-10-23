
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
	CListCtrl	m_Int_List;
	CListCtrl	m_Win_List;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//********************** CUSTOM ******************************	
private:
	//Variables
	CWnd*			m_about_dlg;
	int				m_select_tab;
	DWORD			m_privilage;
	int				m_win_str_sec , m_int_str_sec;
	CString			m_win_str_time , m_int_str_time;
	CString			m_internet_total , m_windows_total;
	CMenu*			m_pop_menu;
	CFont			m_font_win , m_font_int;
	CMyCounter		m_win_counter,m_int_counter;
	CMyServerPort	m_my_api;
	char			m_res_intofflable[50];
	char			m_res_intconlable[50];
	char			m_res_winlable[50];
	char			m_res_wintip[30];
	char			m_res_intofftip[30];
	char			m_res_intcontip[30];
	CString			m_res_zerotime;
	CFile			m_file_con_info;
	//Functions
	#ifdef _DEBUG
		bool	Fake_Connection();
	#endif

		int		FindLatsSlash(CString *path);
inline	void	SetTip(int mode,int prayority,CString* win_duration,CString* int_duration);
inline	void	SetLable(int mode,CString* win_duration,CString* int_duration);
		void	SetUpTray(DWORD Task,char* tip,int size);
		void	StartUp();
		void	TimerMain();
		void	ShutDown();
		void	SetUpDialog();
		void	SaveWindowPos();
		void	ShowAboutBox();
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__96E11F88_523A_4147_9E48_88B541251266__INCLUDED_)
