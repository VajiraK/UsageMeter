// UtilityDlg.h : header file
//

#if !defined(AFX_UTILITYDLG_H__0AF96B26_14AF_4277_8E5A_EFAB022DE348__INCLUDED_)
#define AFX_UTILITYDLG_H__0AF96B26_14AF_4277_8E5A_EFAB022DE348__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUtilityDlg dialog

class CUtilityDlg : public CDialog
{
// Construction
public:
	CUtilityDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUtilityDlg)
	enum { IDD = IDD_UTILITY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUtilityDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUtilityDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UTILITYDLG_H__0AF96B26_14AF_4277_8E5A_EFAB022DE348__INCLUDED_)
