// CMainDlg.h : header file
//

#if !defined(AFX_CMAINDLG_H__7255AF55_94EF_4285_8187_65514E9B480A__INCLUDED_)
#define AFX_CMAINDLG_H__7255AF55_94EF_4285_8187_65514E9B480A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyLogFile.h"

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CDialog
{
// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_FILEVIEWER_DIALOG };
	CStatic	m_int_lable;
	CStatic	m_win_lable;
	CListCtrl	m_Win_List;
	CListCtrl	m_Int_List;
	CTabCtrl	m_Tab_Ctrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
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
	afx_msg void OnFileClose();
	afx_msg void OnAboutbox();
	afx_msg void OnFileOpen();
	afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CFont		m_font_win , m_font_int;
	CMyLogFile	m_logfilobj;
	void		SetUpDialog();
public:
	CString		com_line;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMAINDLG_H__7255AF55_94EF_4285_8187_65514E9B480A__INCLUDED_)
