#if !defined(AFX_DLGPATH_H__4B2F9AA0_2912_459C_A49F_05D2E6871AA1__INCLUDED_)
#define AFX_DLGPATH_H__4B2F9AA0_2912_459C_A49F_05D2E6871AA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPath dialog

#include  "MyRegistry.h"

class CDlgPath : public CDialog
{
// Construction
public:
	CDlgPath(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPath)
	enum { IDD = IDD_DIALOG_PATH };
	CEdit	m_txt_path;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPath)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void MySleep();
	CMyRegistry m_clsreg;
	bool		m_bypass;
public:
	DWORD*		m_pprivilage;
	CString*	m_plogpath;
	bool		m_errer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPATH_H__4B2F9AA0_2912_459C_A49F_05D2E6871AA1__INCLUDED_)
